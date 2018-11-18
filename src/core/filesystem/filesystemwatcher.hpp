#ifndef FS_FILESYSTEMWATCHER_HPP
#define FS_FILESYSTEMWATCHER_HPP

#include <QFileSystemWatcher>
#include <QTimer>

namespace fs
{

class FileSystemWatcher : public QObject
{
    Q_OBJECT

public:
    explicit FileSystemWatcher(QObject *parent = nullptr);

    void addPath(const QString &path);
    void addPaths(const QStringList &paths);

    void removePath(const QString &path);
    void removePaths(const QStringList &paths);

signals:
    void fileChanged(const QString &file);
    void dirChanged(const QString &dir);

private slots:
    void onFileChanged(const QString &file);
    void onDirectoryChanged(const QString &dir);
    void onTimerTimeout();

private:
    static qint64 dirSize(const QString &dir);

    QFileSystemWatcher m_watcher;
    QTimer m_timer;
    QString m_bufferedDir;
    bool m_ignoreDir;
    qint64 m_lastSize;
};

}

#endif // FS_FILESYSTEMWATCHER_HPP
