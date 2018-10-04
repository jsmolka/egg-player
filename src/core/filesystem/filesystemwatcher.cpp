#include "filesystemwatcher.hpp"

#include <QFileInfo>

FileSystemWatcher::FileSystemWatcher(QObject *parent)
    : QObject(parent)
    , m_watcher(this)
    , m_timer(this)
    , m_ignoreDir(false)
{
    connect(&m_watcher, &QFileSystemWatcher::fileChanged, this, &FileSystemWatcher::onFileChanged);
    connect(&m_watcher, &QFileSystemWatcher::directoryChanged, this, &FileSystemWatcher::onDirectoryChanged);
    connect(&m_timer, &QTimer::timeout, this, &FileSystemWatcher::onTimerTimeout);

    m_timer.setSingleShot(true);
}

void FileSystemWatcher::setBufferDuration(int duration)
{
    m_bufferDuration = duration;
}

int FileSystemWatcher::bufferDuration() const
{
    return m_bufferDuration;
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

void FileSystemWatcher::onFileChanged(const File &file)
{
    if (QFileInfo::exists(file))
    {
        m_ignoreDir = true;

        emit fileChanged(file);
    }
}

void FileSystemWatcher::onDirectoryChanged(const Path &dir)
{
    if (m_bufferedDir.isNull() || m_bufferedDir.contains(dir))
        m_bufferedDir = dir;

    m_timer.start(m_bufferDuration);
}

void FileSystemWatcher::onTimerTimeout()
{
    if (!m_ignoreDir)
        emit directoryChanged(m_bufferedDir);

    m_bufferedDir = Path();
    m_ignoreDir = false;
}
