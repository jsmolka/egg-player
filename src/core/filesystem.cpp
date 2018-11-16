#include "filesystem.hpp"

#include <QFileInfo>

#include "core/logger.hpp"
#include "core/macros.hpp"

FileSystem::FileSystem(QObject *parent)
    : QObject(parent)
    , m_watcher(this)
{
    connect(&m_watcher, &fs::FileSystemWatcher::fileChanged, this, &FileSystem::onFileChanged);
    connect(&m_watcher, &fs::FileSystemWatcher::directoryChanged, this, &FileSystem::onDirectoryChanged);
}

Bimap<QString, fs::UniqueFileInfo> FileSystem::uniqueInfo() const
{
    return m_unique;
}

QHash<QString, fs::Directory *> FileSystem::dirs() const
{
    return m_dirs;
}

QHash<QString, Audio *> FileSystem::audios() const
{
    return m_audios;
}

const fs::FileSystemWatcher &FileSystem::watcher() const
{
    return m_watcher;
}

fs::FileSystemWatcher &FileSystem::watcher()
{
    return EGG_REF_CAST(FileSystem, fs::FileSystemWatcher, watcher);
}

void FileSystem::addPath(const QString &path)
{
    if (m_dirs.contains(path))
        return;

    fs::Directory *dir = new fs::Directory(path, this);
    connect(dir, &fs::Directory::parsed, this, &FileSystem::onDirParsed);
    connect(dir, &fs::Directory::created, this, &FileSystem::onDirCreated);
    connect(dir, &fs::Directory::removed, this, &FileSystem::onDirRemoved);
    dir->parse();
}

QStrings FileSystem::globFiles() const
{
    QStrings files;
    for (fs::Directory *dir : qAsConst(m_dirs))
        files << dir->globAudios(fs::Directory::GlobPolicy::Shallow);

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

void FileSystem::onDirParsed(fs::Directory *dir)
{
    QStringList paths;
    paths << dir->path();
    for (const QString &file : dir->files())
    {
        paths << file;
        m_unique.insert(file, fs::UniqueFileInfo(file));
    }
    m_watcher.addPaths(paths);
    m_dirs.insert(dir->path(), dir);
}

void FileSystem::onDirCreated(fs::Directory *dir)
{
    m_watcher.addPath(dir->path());
    m_dirs.insert(dir->path(), dir);
}

void FileSystem::onDirRemoved(fs::Directory *dir)
{
    m_watcher.removePath(dir->path());
    m_dirs.remove(dir->path());
    dir->deleteLater();
}

void FileSystem::onFileChanged(const QString &file)
{
    processModified(file);
}

void FileSystem::onDirectoryChanged(const QString &path)
{
    fs::Directory *dir = m_dirs.value(path, nullptr);
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
            newInfos.insert(fs::UniqueFileInfo(file), file);
    }
}

void FileSystem::triggerEvents(InfoHash &oldInfos, InfoHash &newInfos)
{
    for (auto iter = oldInfos.cbegin(); iter != oldInfos.cend(); ++iter)
    {
        const fs::UniqueFileInfo info = iter.key();
        if (newInfos.contains(info))
        {
            processRenamed(iter.value(), newInfos.value(info));
            newInfos.remove(info);
        }
        else
        {
            processRemoved(iter.value());
        }
    }

    for (auto iter = newInfos.cbegin(); iter != newInfos.cend(); ++iter)
        processAdded(iter.value(), iter.key());
}

void FileSystem::processModified(const QString &file)
{
    if (m_audios.contains(file))
        emit modified(m_audios.value(file));
}

void FileSystem::processRenamed(const QString &from, const QString &to)
{
    m_watcher.removePath(from);
    m_watcher.addPath(to);

    const fs::UniqueFileInfo info = m_unique.value(from);
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

void FileSystem::processAdded(const QString &file, const fs::UniqueFileInfo &info)
{
    m_watcher.addPath(file);
    m_unique.insert(file, info);
    emit added(file);
}

void FileSystem::processRemoved(const QString &file)
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
