#include "filesystem.hpp"

FileSystem::FileSystem(QObject *parent)
    : QObject(parent)
{

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
    return result;
}

void FileSystem::onDirParsed(Directory *dir)
{
    m_dirs.insert(dir->path(), dir);
}
