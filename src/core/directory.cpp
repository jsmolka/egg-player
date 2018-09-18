#include "directory.hpp"

#include <QDirIterator>

Directory::Directory(QObject *parent)
    : Directory(Path(), parent)
{

}

Directory::Directory(const Path &path, QObject *parent)
    : QObject(parent)
    , m_path(path)
{

}

Path Directory::path() const
{
    return m_path;
}

QSet<File> Directory::files() const
{
    return m_files;
}

QHash<Path, Directory *> Directory::dirs() const
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
        dirIter.next();
        if (dirIter.fileInfo().isDir())
        {
            const Path path = dirIter.filePath();
            Directory *dir = new Directory(path, this);
            connect(dir, &Directory::parsed, this, &Directory::parsed);
            connect(dir, &Directory::created, this, &Directory::created);
            connect(dir, &Directory::removed, this, &Directory::removed);
            dir->parse();
            m_dirs.insert(path, dir);
        }
        else
        {
            const File file = dirIter.filePath();
            if (file.endsWith(QLatin1String(".mp3"), Qt::CaseInsensitive))
                m_files << file;
        }
    }
    emit parsed(this);
}

Files Directory::globAudios(bool recursive) const
{
    Files files;
    for (const File &file : qAsConst(m_files))
        files << file;

    if (recursive)
    {
        for (Directory *dir : qAsConst(m_dirs))
            files << dir->globAudios(recursive);
    }
    return files;
}

Files Directory::processChanges()
{
    Files changes;

    processRemovedDirChanges(changes);
    processExistingDirChanges(changes);
    processFileChanges(changes);

    return changes;
}

void Directory::processRemovedDirChanges(Files &changes)
{
    for (Directory *dir : qAsConst(m_dirs))
    {
        if (!dir->exists())
        {
            changes << dir->globAudios(false);
            m_dirs.remove(dir->path());
            emit removed(dir);
        }
    }
}

void Directory::processExistingDirChanges(Files &changes)
{
    QDirIterator dirIter(m_path, QDir::Dirs | QDir::NoDotAndDotDot);
    while (dirIter.hasNext())
    {
        dirIter.next();
        const Path path = dirIter.filePath();
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

void Directory::processFileChanges(Files &changes)
{
    if (!exists())
    {
        changes << globAudios(false);
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
        dirIter.next();
        const File file = dirIter.filePath();
        if (!m_files.contains(file))
        {
            changes << file;
            m_files.insert(file);
        }
    }
}
