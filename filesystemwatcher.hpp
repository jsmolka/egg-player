#ifndef FILESYSTEMWATCHER_HPP
#define FILESYSTEMWATCHER_HPP

#include "audio.hpp"

#include <QFileSystemWatcher>
#include <QObject>

class FileSystemWatcher : public QObject
{
    Q_OBJECT

public:
    FileSystemWatcher(QObject *parent = nullptr);
    ~FileSystemWatcher();

    void watch(Audio *audio);

private slots:
    void onWatcherFileChanged(const QString &file);
    void onWatcherDirectoryChanged(const QString &directory);

private:
    QFileSystemWatcher m_watcher;
};

#endif // FILESYSTEMWATCHER_HPP
