#include "filesystemwatcher.hpp"

FileSystemWatcher::FileSystemWatcher(QObject *parent)
    : QObject(parent)
    , m_watcher(this)
{
    connect(&m_watcher, &QFileSystemWatcher::fileChanged, this, &FileSystemWatcher::onWatcherFileChanged);
    connect(&m_watcher, &QFileSystemWatcher::directoryChanged, this, &FileSystemWatcher::onWatcherDirectoryChanged);
}

FileSystemWatcher::~FileSystemWatcher()
{

}

void FileSystemWatcher::watch(Audio *audio)
{
    m_watcher.addPath(audio->path());
}

void FileSystemWatcher::onWatcherFileChanged(const QString &file)
{
    qDebug() << "File changed:" << file;
}

void FileSystemWatcher::onWatcherDirectoryChanged(const QString &directory)
{
    qDebug() << "Dir changed:" << directory;
}
