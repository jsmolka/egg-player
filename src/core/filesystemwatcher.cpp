#include "filesystemwatcher.hpp"

#include <QtGlobal>

FileSystemWatcher::FileSystemWatcher(QObject *parent)
    : QObject(parent)
    , m_watcher(this)
    , m_timer(this)
    , m_bufferDuration(200)
{
    connect(&m_watcher, &QFileSystemWatcher::fileChanged, this, &FileSystemWatcher::fileChanged);
    connect(&m_watcher, &QFileSystemWatcher::directoryChanged, this, &FileSystemWatcher::onDirectoryChanged);

    connect(&m_timer, &QTimer::timeout, this, &FileSystemWatcher::onTimeout);
    m_timer.setSingleShot(true);
}

void FileSystemWatcher::addPath(const Path &path)
{
    m_watcher.addPath(path);
}

void FileSystemWatcher::addPaths(const QStringList &paths)
{
    m_watcher.addPaths(paths);
}

void FileSystemWatcher::removePath(const Path &path)
{
    m_watcher.removePath(path);
}

void FileSystemWatcher::removePaths(const QStringList &paths)
{
    m_watcher.removePaths(paths);
}

void FileSystemWatcher::setBufferDuration(int duration)
{
    m_bufferDuration = duration;
}

int FileSystemWatcher::bufferDuration() const
{
    return m_bufferDuration;
}

void FileSystemWatcher::onDirectoryChanged(const Path &dir)
{
    queueDirectory(dir);

    m_timer.start(m_bufferDuration);
}

void FileSystemWatcher::onTimeout()
{
    for (const Path &path : qAsConst(m_buffer))
        emit directoryChanged(path);

    m_buffer.clear();
}

void FileSystemWatcher::queueDirectory(const Path &dir)
{
    auto iter = m_buffer.begin();
    while (iter != m_buffer.end())
    {
        if (dir.contains(*iter))
            return;

        if ((*iter).contains(dir))
            iter = m_buffer.erase(iter);
        else
            ++iter;
    }
    m_buffer << dir;
}
