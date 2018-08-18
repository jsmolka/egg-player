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
    connect(dir, &Directory::created, this, &FileSystem::onDirCreated);
    connect(dir, &Directory::removed, this, &FileSystem::onDirRemoved);
    dir->parse();
}

Files FileSystem::globAudios() const
{
    Files result;
    QHashIterator<Path, Directory *> iter(m_dirs);
    while (iter.hasNext())
    {
        iter.next();
        for (const File &file : iter.value()->files())
            result << file;
    }
    return result;
}

void FileSystem::watchAudio(Audio *audio)
{
    m_audios.insert(audio->path(), audio);
}

void FileSystem::onDirParsed(Directory *dir)
{
    QStringList paths;
    for (const File &file : dir->files())
    {
        paths << file;
        m_unique.insert(file, UniqueFileInfo(file));
    }
    paths << dir->path();

    m_watcher.addPaths(paths);
    m_dirs.insert(dir->path(), dir);
}

void FileSystem::onDirCreated(Directory *dir)
{
    m_watcher.addPath(dir->path());
    m_dirs.insert(dir->path(), dir);
}

void FileSystem::onDirRemoved(Directory *dir)
{
    m_watcher.removePath(dir->path());
    m_dirs.remove(dir->path());
}

void FileSystem::onFileChanged(const File &file)
{
    if (QFileInfo(file).exists())
        eventModified(file);
}

void FileSystem::onDirectoryChanged(const Path &dir)
{
    const Files files = m_dirs.value(dir)->processChanges();
    QHash<UniqueFileInfo, File> renamedFrom;
    QHash<UniqueFileInfo, File> renamedTo;
    for (const File file : files)
    {
        if (m_unique.contains(file))
            renamedFrom.insert(m_unique.value(file), file);
        else
            renamedTo.insert(UniqueFileInfo(file), file);
    }

    QHashIterator<UniqueFileInfo, File> iter(renamedFrom);
    while (iter.hasNext())
    {
        iter.next();
        const UniqueFileInfo info = iter.key();
        if (renamedTo.contains(info))
        {
            eventRenamed(iter.value(), renamedTo.value(info));
            renamedTo.remove(info);
        }
        else
        {
            eventRemoved(iter.value());
        }
    }

    iter = QHashIterator<UniqueFileInfo, File>(renamedTo);
    while (iter.hasNext())
    {
        iter.next();
        eventAdded(iter.value());
    }
}

void FileSystem::eventModified(const File &file)
{
    if (m_audios.contains(file))
        emit modified(m_audios.value(file));
}

void FileSystem::eventRenamed(const File &from, const File &to)
{
    m_watcher.removePath(from);
    m_watcher.addPath(to);

    const UniqueFileInfo info = m_unique.value(from);
    m_unique.remove(from);
    m_unique.insert(to, info);

    if (m_audios.contains(from))
    {
        emit renamed(m_audios.value(from), to);
        m_audios.insert(to, m_audios.value(from));
        m_audios.remove(from);
    }
}

void FileSystem::eventAdded(const File &file)
{
    m_watcher.addPath(file);
    m_unique.insert(file, UniqueFileInfo(file));

    emit added(file);
}

void FileSystem::eventRemoved(const File &file)
{
    m_watcher.removePath(file);
    m_unique.remove(file);

    if (m_audios.contains(file))
    {
        emit removed(m_audios.value(file));
        m_audios.remove(file);
    }
}
