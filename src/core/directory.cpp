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

void Directory::setPath(const Path &path)
{
    m_path = path;
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
    QDirIterator iter(m_path, QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    while (iter.hasNext())
    {
        iter.next();
        const File file = iter.filePath();
        if (iter.fileInfo().isDir())
        {
            Directory *dir = new Directory(file, this);
            connect(dir, &Directory::parsed, this, &Directory::parsed);
            connect(dir, &Directory::created, this, &Directory::created);
            connect(dir, &Directory::removed, this, &Directory::removed);
            dir->parse();
            m_dirs.insert(file, dir);
        }
        else
        {
            if (file.endsWith(QLatin1String(".mp3"), Qt::CaseInsensitive))
                m_files << file;
        }
    }
    emit parsed(this);
}

Files Directory::processChanges()
{
    Files changes;

    processDirChanges(changes);
    processFileChanges(changes);

    return changes;
}

void Directory::processDirChanges(Files &changes)
{
    for (auto iter = m_dirs.cbegin(); iter != m_dirs.cend(); ++iter)
    {
        Directory *dir = iter.value();
        if (!dir->exists())
        {
            for (const File &file : dir->files())
                changes << file;

            m_dirs.remove(dir->path());
            emit removed(dir);
        }
    }

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
    if (!QFileInfo::exists(m_path))
    {
        for (const File &file : qAsConst(m_files))
            changes << file;

        emit removed(this);
    }
    else
    {
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
}
