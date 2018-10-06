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
    static qint64 dirSize(const Path &dir);

    static constexpr int s_bufferDuration{500};

    QFileSystemWatcher m_watcher;
    QTimer m_timer;
    Path m_bufferedDir;
    bool m_ignoreDir;
    qint64 m_lastSize;
};

#endif // FILESYSTEMWATCHER_HPP
