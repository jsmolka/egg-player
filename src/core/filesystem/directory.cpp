#include "directory.hpp"

#include <QDirIterator>

#include "core/utils.hpp"

fs::Directory::Directory(QObject *parent)
    : Directory(QString(), parent)
{

}

fs::Directory::Directory(const QString &path, QObject *parent)
    : QObject(parent)
    , m_path(path)
{

}

QString fs::Directory::path() const
{
    return m_path;
}

QSet<QString> fs::Directory::files() const
{
    return m_files;
}

QHash<QString, fs::Directory *> fs::Directory::dirs() const
{
    return m_dirs;
}

bool fs::Directory::exists() const
{
    return QDir(m_path).exists();
}

void fs::Directory::parse()
{
    QDirIterator iter(m_path, QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    while (iter.hasNext())
    {
        const QString file = iter.next();
        const QFileInfo info = iter.fileInfo();

        if (info.isFile())
        {
            if (Util::isAudioFile(file))
                m_files << file;
        }
        if (info.isDir())
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

QStrings fs::Directory::globAudios(GlobPolicy policy) const
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

QStrings fs::Directory::processChanges()
{
    QStrings changes;

    processRemovedDirChanges(changes);
    processExistingDirChanges(changes);
    processFileChanges(changes);

    return changes;
}

void fs::Directory::processRemovedDirChanges(QStrings &changes)
{
    for (auto iter = m_dirs.begin(); iter != m_dirs.end(); )
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

void fs::Directory::processExistingDirChanges(QStrings &changes)
{
    QDirIterator iter(m_path, QDir::Dirs | QDir::NoDotAndDotDot);
    while (iter.hasNext())
    {
        const QString path = iter.next();
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

void fs::Directory::processFileChanges(QStrings &changes)
{
    if (!exists())
    {
        changes << globAudios(GlobPolicy::Shallow);
        emit removed(this);
        return;
    }

    for (auto iter = m_files.begin(); iter != m_files.end(); )
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

    QDirIterator iter(m_path, QStringList() << "*.mp3", QDir::Files);
    while (iter.hasNext())
    {
        const QString file = iter.next();
        if (!m_files.contains(file))
        {
            changes << file;
            m_files.insert(file);
        }
    }
}
