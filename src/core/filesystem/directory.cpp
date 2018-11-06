#include "directory.hpp"

#include <QDirIterator>

Directory::Directory(QObject *parent)
    : Directory(QString(), parent)
{

}

Directory::Directory(const QString &path, QObject *parent)
    : QObject(parent)
    , m_path(path)
{

}

QString Directory::path() const
{
    return m_path;
}

QSet<QString> Directory::files() const
{
    return m_files;
}

QHash<QString, Directory *> Directory::dirs() const
{
    return m_dirs;
}

bool Directory::exists() const
{
    return QDir(m_path).exists();
}

void Directory::parse()
{
    QDirIterator dirIter(m_path, QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    while (dirIter.hasNext())
    {
        const QString file = dirIter.next();
        const QFileInfo info = dirIter.fileInfo();
        if (info.isFile())
        {
            if (file.endsWith(".mp3", Qt::CaseInsensitive))
                m_files << file;
        }
        else if (info.isDir())
        {
            Directory *dir = new Directory(file, this);
            connect(dir, &Directory::parsed, this, &Directory::parsed);
            connect(dir, &Directory::created, this, &Directory::created);
            connect(dir, &Directory::removed, this, &Directory::removed);
            dir->parse();

            m_dirs.insert(file, dir);
        }
    }
    emit parsed(this);
}

QStrings Directory::globAudios(GlobPolicy policy) const
{
    QStrings files;
    for (const QString &file : qAsConst(m_files))
        files << file;

    if (policy == GlobPolicy::Recursive)
    {
        for (Directory *dir : qAsConst(m_dirs))
            files << dir->globAudios(policy);
    }
    return files;
}

QStrings Directory::processChanges()
{
    QStrings changes;

    processRemovedDirChanges(changes);
    processExistingDirChanges(changes);
    processFileChanges(changes);

    return changes;
}

void Directory::processRemovedDirChanges(QStrings &changes)
{
    auto iter = m_dirs.begin();
    while (iter != m_dirs.end())
    {
        Directory *dir = iter.value();
        if (!dir->exists())
        {
            changes << dir->globAudios(GlobPolicy::Shallow);
            iter = m_dirs.erase(iter);
            emit removed(dir);
        }
        else
        {
            ++iter;
        }
    }
}

void Directory::processExistingDirChanges(QStrings &changes)
{
    QDirIterator dirIter(m_path, QDir::Dirs | QDir::NoDotAndDotDot);
    while (dirIter.hasNext())
    {
        const QString path = dirIter.next();
        Directory *dir = m_dirs.value(path, nullptr);
        if (!dir)
        {
            dir = new Directory(path, this);
            connect(dir, &Directory::created, this, &Directory::created);
            connect(dir, &Directory::removed, this, &Directory::removed);

            m_dirs.insert(path, dir);
            emit created(dir);
        }
        changes << dir->processChanges();
    }
}

void Directory::processFileChanges(QStrings &changes)
{
    if (!exists())
    {
        changes << globAudios(GlobPolicy::Shallow);
        emit removed(this);
        return;
    }

    auto iter = m_files.begin();
    while (iter != m_files.end())
    {
        if (!QFileInfo::exists(*iter))
        {
            changes << *iter;
            iter = m_files.erase(iter);
        }
        else
        {
            ++iter;
        }
    }

    QDirIterator dirIter(m_path, QStringList() << "*.mp3", QDir::Files);
    while (dirIter.hasNext())
    {
        const QString file = dirIter.next();
        if (!m_files.contains(file))
        {
            changes << file;
            m_files.insert(file);
        }
    }
}
