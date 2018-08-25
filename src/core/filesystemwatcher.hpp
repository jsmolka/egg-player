#ifndef FILESYSTEMWATCHER_HPP
#define FILESYSTEMWATCHER_HPP

#include <QFileSystemWatcher>
#include <QSet>
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
    void onDirectoryChanged(const Path &dir);
    void onTimeout();

private:
    void queueDirectory(const Path &dir);

    QFileSystemWatcher m_watcher;
    QSet<Path> m_buffer;
    QTimer m_timer;

    int m_bufferDuration;
};

#endif // FILESYSTEMWATCHER_HPP
