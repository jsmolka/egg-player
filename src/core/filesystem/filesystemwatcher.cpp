#include "filesystemwatcher.hpp"

#include <QDirIterator>
#include <QFileInfo>

FileSystemWatcher::FileSystemWatcher(QObject *parent)
    : QObject(parent)
    , m_watcher(this)
    , m_timer(this)
    , m_ignoreDir(false)
    , m_lastSize(0)
{
    connect(&m_watcher, &QFileSystemWatcher::fileChanged, this, &FileSystemWatcher::onFileChanged);
    connect(&m_watcher, &QFileSystemWatcher::directoryChanged, this, &FileSystemWatcher::onDirectoryChanged);
    connect(&m_timer, &QTimer::timeout, this, &FileSystemWatcher::onTimerTimeout);

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

    m_timer.start(s_bufferDuration);
}

void FileSystemWatcher::onTimerTimeout()
{
    if (!m_ignoreDir)
    {
        const qint64 size = dirSize(m_bufferedDir);
        if (size != m_lastSize)
        {
            m_lastSize = size;
            m_timer.start(s_bufferDuration);
            return;
        }
        emit directoryChanged(m_bufferedDir);
    }
    m_bufferedDir = Path();
    m_ignoreDir = false;
    m_lastSize = 0;
}

qint64 FileSystemWatcher::dirSize(const Path &dir)
{
    qint64 size = 0;
    QDirIterator dirIter(dir, QDir::Files, QDirIterator::Subdirectories);
    while (dirIter.hasNext())
    {
        dirIter.next();
        size += dirIter.fileInfo().size();
    }
    return size;
}
