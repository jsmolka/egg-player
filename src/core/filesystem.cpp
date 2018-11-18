#include "filesystem.hpp"

#include <QDir>
#include <QFileInfo>

#include "core/logger.hpp"

FileSystem::FileSystem(QObject *parent)
    : QObject(parent)
    , m_watcher(this)
{
    connect(&m_watcher, &fs::FileSystemWatcher::fileChanged, this, &FileSystem::onFileChanged);
    connect(&m_watcher, &fs::FileSystemWatcher::dirChanged, this, &FileSystem::onDirChanged);
}

void FileSystem::addPath(const QString &path)
{
    if (m_dirs.contains(path))
        return;

    fs::Directory *dir = new fs::Directory(path, this);
    dir->init();

    addDir(dir);
}

void FileSystem::addFile(const QString &file)
{
    const QString path = QFileInfo(file).dir().absolutePath();

    if (!m_dirs.contains(path))
    {
        addPath(path);

        fs::Directory *dir = m_dirs.value(path);
        ignoreDirAdds(dir);
        ignoreDirFiles(dir);
    }
    else
    {
        m_watcher.addPath(file);
    }
    m_ignored.remove(file);
}

QStrings FileSystem::globFiles() const
{
    QStrings files;
    for (fs::Directory *dir : m_dirs)
        files << globDirFiles(dir, GlobPolicy::Shallow);

    return files;
}

QStrings FileSystem::globDirFiles(const QString &path, GlobPolicy policy) const
{
    return m_dirs.contains(path)
        ? globDirFiles(m_dirs.value(path), policy)
        : QStrings();
}

void FileSystem::watchAudio(Audio *audio)
{
    m_watched.insert(audio->file(), audio);
}

void FileSystem::unwatchAudio(Audio *audio)
{
    m_watched.remove(audio->file());
}

bool FileSystem::containsFile(const QString &file) const
{
    return m_unique.contains(file);
}

bool FileSystem::containsDir(const QString &dir) const
{
    return m_dirs.contains(dir);
}

bool FileSystem::isIgnored(const QString &file) const
{
    return m_ignored.contains(file);
}

void FileSystem::onDirAdded(fs::Directory *dir)
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

void FileSystem::onDirChanged(const QString &path)
{
    fs::Directory *dir = m_dirs.value(path, nullptr);
    if (!dir)
    {
        EGG_LOG("Changed directory does not exist %1", path);
        return;
    }
    QStrings changes = dir->update();

    QStrings added;
    QSet<QString> deleted;

    for (const QString &file : changes)
    {
        if (m_unique.contains(file))
        {
            deleted << file;
        }
        else if (QFileInfo::exists(file))
        {
            const fs::UniqueFileInfo info(file);
            if (m_unique.contains(info))
            {
                const QString from = m_unique.value(info);
                processRenamed(from, file);
                deleted.remove(from);
            }
            else
            {
                processAdded(file, info);
                added << file;
            }
        }
    }

    for (const QString &file : deleted)
        processRemoved(file);

    if (!added.isEmpty())
        emit this->added(added);
}

void FileSystem::addDir(fs::Directory *dir)
{
    connect(dir, &fs::Directory::added, this, &FileSystem::onDirAdded);
    connect(dir, &fs::Directory::removed, this, &FileSystem::onDirRemoved);

    for (fs::Directory *subdir : dir->subdirs())
        addDir(subdir);

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

QStrings FileSystem::globDirFiles(fs::Directory *dir, FileSystem::GlobPolicy policy) const
{
    QStrings files;
    if (policy == GlobPolicy::Recursive)
    {
        for (fs::Directory *subdir : dir->subdirs())
            globDirFiles(subdir, policy);
    }

    for (const QString &file : dir->files())
    {
        if (!m_ignored.contains(file))
            files << file;
    }
    return files;
}

void FileSystem::ignoreDirFiles(fs::Directory *dir)
{
    for (fs::Directory *subdir : dir->subdirs())
        ignoreDirFiles(subdir);

    QStringList unwatch;
    for (const QString &file : dir->files())
    {
        m_ignored << file;
        unwatch << file;
    }
    m_watcher.removePaths(unwatch);
}

void FileSystem::ignoreDirAdds(fs::Directory *dir)
{
    for (fs::Directory *subdir : dir->subdirs())
        ignoreDirAdds(subdir);

    dir->setAddPolicy(fs::Directory::AddPolicy::Ignore);
}

void FileSystem::processAdded(const QString &file, const fs::UniqueFileInfo &info)
{
    m_watcher.addPath(file);
    m_unique.insert(file, info);
}

void FileSystem::processRemoved(const QString &file)
{
    m_watcher.removePath(file);
    m_unique.remove(file);
    m_ignored.remove(file);

    if (m_watched.contains(file))
    {
        Audio *audio = m_watched.value(file);
        m_watched.remove(file);
        emit removed(audio);
    }
}

void FileSystem::processModified(const QString &file)
{
    if (m_watched.contains(file))
        emit modified(m_watched.value(file));
}

void FileSystem::processRenamed(const QString &from, const QString &to)
{
    m_watcher.removePath(from);
    m_watcher.addPath(to);

    const fs::UniqueFileInfo info = m_unique.value(from);
    m_unique.remove(from);
    m_unique.insert(to, info);

    if (m_ignored.contains(from))
    {
        m_ignored.remove(from);
        m_ignored << to;
    }

    if (m_watched.contains(from))
    {
        Audio *audio = m_watched.value(from);
        m_watched.remove(from);
        m_watched.insert(to, audio);
        emit renamed(audio, to);
    }
}
