#include "filesystemwatcher.hpp"

FileSystemWatcher::FileSystemWatcher(QObject *parent)
    : QObject(parent)
    , m_watcher(this)
    , m_bufferDuration(200)
{
    connect(&m_watcher, &QFileSystemWatcher::fileChanged, this, &FileSystemWatcher::fileChanged);
    connect(&m_watcher, &QFileSystemWatcher::directoryChanged, this, &FileSystemWatcher::onDirectoryChanged);

    connect(&m_timer, &QTimer::timeout, this, &FileSystemWatcher::onTimeout);
}

FileSystemWatcher::~FileSystemWatcher()
{

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
    m_buffer << dir;
    m_timer.start(m_bufferDuration);
}

void FileSystemWatcher::onTimeout()
{
    m_timer.stop();
    for (const Path path : m_buffer)
        emit directoryChanged(path);
    m_buffer.clear();
}
