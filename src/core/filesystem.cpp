#include "filesystem.hpp"

#include <QFileInfo>

#include "core/logger.hpp"
#include "core/macros.hpp"

FileSystem::FileSystem(QObject *parent)
    : QObject(parent)
    , m_watcher(this)
{
    connect(&m_watcher, &FileSystemWatcher::fileChanged, this, &FileSystem::onFileChanged);
    connect(&m_watcher, &FileSystemWatcher::directoryChanged, this, &FileSystem::onDirectoryChanged);
}

Bimap<QString, UniqueFileInfo> FileSystem::uniqueInfo() const
{
    return m_unique;
}

QHash<QString, Directory *> FileSystem::dirs() const
{
    return m_dirs;
}

QHash<QString, Audio *> FileSystem::audios() const
{
    return m_audios;
}

const FileSystemWatcher &FileSystem::watcher() const
{
    return m_watcher;
}

FileSystemWatcher &FileSystem::watcher()
{
    return EGG_REF_CAST(FileSystem, FileSystemWatcher, watcher);
}

void FileSystem::addPath(const QString &path)
{
    if (m_dirs.contains(path))
        return;

    Directory *dir = new Directory(path, this);
    connect(dir, &Directory::parsed, this, &FileSystem::onDirParsed);
    connect(dir, &Directory::created, this, &FileSystem::onDirCreated);
    connect(dir, &Directory::removed, this, &FileSystem::onDirRemoved);
    dir->parse();
}

QStrings FileSystem::globFiles() const
{
    QStrings files;
    for (Directory *dir : qAsConst(m_dirs))
        files << dir->globAudios(Directory::GlobPolicy::Shallow);

    return files;
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
    paths << dir->path();
    for (const QString &file : dir->files())
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

void FileSystem::onFileChanged(const QString &file)
{
    eventModified(file);
}

void FileSystem::onDirectoryChanged(const QString &path)
{
    Directory *dir = m_dirs.value(path, nullptr);
    if (!dir)
    {
        EGG_LOG("Changed directory does not exist %1", path);
        return;
    }

    InfoHash oldInfos;
    InfoHash newInfos;
    const QStrings changes = dir->processChanges();

    processChanges(changes, oldInfos, newInfos);
    triggerEvents(oldInfos, newInfos);
}

void FileSystem::processChanges(const QStrings &changes, InfoHash &oldInfos, InfoHash &newInfos)
{
    for (const QString &file : changes)
    {
        if (m_unique.contains(file))
            oldInfos.insert(m_unique.value(file), file);
        else
            newInfos.insert(UniqueFileInfo(file), file);
    }
}

void FileSystem::triggerEvents(InfoHash &oldInfos, InfoHash &newInfos)
{
    for (auto iter = oldInfos.cbegin(); iter != oldInfos.cend(); ++iter)
    {
        const UniqueFileInfo info = iter.key();
        if (newInfos.contains(info))
        {
            eventRenamed(iter.value(), newInfos.value(info));
            newInfos.remove(info);
        }
        else
        {
            eventRemoved(iter.value());
        }
    }

    for (auto iter = newInfos.cbegin(); iter != newInfos.cend(); ++iter)
        eventAdded(iter.value(), iter.key());
}

void FileSystem::eventModified(const QString &file)
{
    if (m_audios.contains(file))
        emit modified(m_audios.value(file));
}

void FileSystem::eventRenamed(const QString &from, const QString &to)
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

void FileSystem::eventAdded(const QString &file, const UniqueFileInfo &info)
{
    m_watcher.addPath(file);
    m_unique.insert(file, info);
    emit added(file);
}

void FileSystem::eventRemoved(const QString &file)
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
