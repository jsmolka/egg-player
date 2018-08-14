#include "filesystem.hpp"

FileSystem::FileSystem(QObject *parent)
    : QObject(parent)
    , m_watcher(this)
{
    connect(&m_watcher, &FileSystemWatcher::fileChanged, this, &FileSystem::onFileChanged);
    connect(&m_watcher, &FileSystemWatcher::directoryChanged, this, &FileSystem::onDirectoryChanged);
}

FileSystem::~FileSystem()
{

}

QHash<Path, Directory *> FileSystem::dirs() const
{
    return m_dirs;
}

void FileSystem::addPath(const Path &path)
{
    Directory *dir = new Directory(path, this);
    connect(dir, &Directory::parsed, this, &FileSystem::onDirParsed);
    dir->parse();
}

Files FileSystem::globAudios() const
{
    Files result;
    QHashIterator<Path, Directory *> iter(m_dirs);
    while (iter.hasNext())
    {
        iter.next();
        result << iter.value()->files();
    }
    // Todo: Maybe reserve space here to const inserting time
    return result;
}

void FileSystem::onDirParsed(Directory *dir)
{
    m_watcher.addPath(dir->path());
    m_dirs.insert(dir->path(), dir);
}

void FileSystem::onFileChanged(const File &file)
{
    qDebug() << "changed file" << file;
}

void FileSystem::onDirectoryChanged(const Path &dir)
{
    qDebug() << "changed dir" << dir;
}
