#ifndef FILESYSTEMWATCHER_HPP
#define FILESYSTEMWATCHER_HPP

#include <QFileSystemWatcher>
#include <QTimer>

#include "types.hpp"

class FileSystemWatcher : public QObject
{
    Q_OBJECT

public:
    explicit FileSystemWatcher(QObject *parent = nullptr);

    void setBufferDuration(int duration);
    int bufferDuration() const;

    void addPath(const Path &path);
    void addPaths(const QStringList &paths);

    void removePath(const Path &path);
    void removePaths(const QStringList &paths);

signals:
    void fileChanged(const File &file);
    void directoryChanged(const Path &dir);

private slots:
    void onFileChanged(const File &file);
    void onDirectoryChanged(const Path &dir);
    void onTimerTimeout();

private:
    QFileSystemWatcher m_watcher;
    QTimer m_timer;

    int m_bufferDuration{1000};
    Path m_bufferedDir;
    bool m_ignoreDir;
};

#endif // FILESYSTEMWATCHER_HPP
