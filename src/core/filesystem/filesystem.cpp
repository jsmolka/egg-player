#include "filesystem.hpp"

#include <QFileInfo>

FileSystem::FileSystem(QObject *parent)
    : QObject(parent)
    , m_watcher(this)
{
    connect(&m_watcher, &FileSystemWatcher::fileChanged, this, &FileSystem::onFileChanged);
    connect(&m_watcher, &FileSystemWatcher::directoryChanged, this, &FileSystem::onDirectoryChanged);
}

Bimap<File, UniqueFileInfo> FileSystem::uniqueInfo() const
{
    return m_unique;
}

QHash<Path, Directory *> FileSystem::dirs() const
{
    return m_dirs;
}

QHash<File, Audio *> FileSystem::audios() const
{
    return m_audios;
}

FileSystemWatcher &FileSystem::watcher()
{
    return m_watcher;
}

void FileSystem::addPath(const Path &path)
{
    if (m_dirs.contains(path))
        return;

    Directory *dir = new Directory(path, this);
    connect(dir, &Directory::parsed, this, &FileSystem::onDirParsed);
    connect(dir, &Directory::created, this, &FileSystem::onDirCreated);
    connect(dir, &Directory::removed, this, &FileSystem::onDirRemoved);
    dir->parse();
}

Files FileSystem::globAudios() const
{
    Files result;
    for (Directory *dir : qAsConst(m_dirs))
        result << dir->globAudios(false);
    return result;
}

void FileSystem::watchAudio(Audio *audio)
{
    m_audios.insert(audio->file(), audio);
}

void FileSystem::unwatchAudio(Audio *audio)
{
    m_audios.remove(audio->file());
}

void FileSystem::onDirParsed(Directory *dir)
{
    QStringList paths;
    paths.reserve(dir->files().size() + 1);
    paths << dir->path();
    for (const File &file : dir->files())
    {
        paths << file;
        m_unique.insert(file, UniqueFileInfo(file));
    }
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
    dir->deleteLater();
}

void FileSystem::onFileChanged(const File &file)
{
    eventModified(file);
}

void FileSystem::onDirectoryChanged(const Path &dir)
{
    const Files files = m_dirs.value(dir)->processChanges();
    QHash<UniqueFileInfo, File> renamedFrom;
    QHash<UniqueFileInfo, File> renamedTo;

    for (const File &file : files)
    {
        if (m_unique.contains(file))
            renamedFrom.insert(m_unique.value(file), file);
        else
            renamedTo.insert(UniqueFileInfo(file), file);
    }

    for (auto iter = renamedFrom.cbegin(); iter != renamedFrom.cend(); ++iter)
    {
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

    for (const File &file : renamedTo)
        eventAdded(file);
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
        Audio *audio = m_audios.value(from);
        m_audios.remove(from);
        m_audios.insert(to, audio);
        emit renamed(audio, to);
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
        Audio *audio = m_audios.value(file);
        m_audios.remove(file);
        emit removed(audio);
    }
}
