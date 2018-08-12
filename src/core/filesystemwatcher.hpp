#ifndef FILESYSTEMWATCHER_HPP
#define FILESYSTEMWATCHER_HPP

#include "audio.hpp"
#include "types.hpp"

#include <QFileInfo>
#include <QFileSystemWatcher>
#include <QHash>
#include <QObject>
#include <QSet>
#include <QTimer>

class FileSystemWatcher : public QObject
{
    Q_OBJECT

public:
    FileSystemWatcher(QObject *parent = nullptr);
    ~FileSystemWatcher();

    static Files globAudios(const QString &path);

    void setBufferDuration(int duration);
    int bufferDuration() const;

    void watchAudio(Audio *audio);
    void watchDir(const QString &dir);

signals:
    void added(const QString &file);
    void removed(Audio *audio);
    void modified(Audio *audio);
    void renamed(Audio *audio, const QString &file);

private slots:
    void onWatcherFileChanged(const QString &file);
    void onWatcherDirChanged(const QString &dir);

    void onFileTimerTimeout();
    void onDirTimerTimeout();

private:
    void fileChanged(const QString &file);
    void dirChanged(const QString &dir);

    void parseDirectory(const QString &dir, bool isRoot = false);

    void eventAdded(const QString &file);
    void eventRemoved(Audio *audio);
    void eventModified(Audio *audio);
    void eventRenamed(Audio *audio, const QString &file);

    QFileSystemWatcher m_watcher;

    QSet<QString> m_fileBuffer;
    QSet<QString> m_dirBuffer;

    QTimer m_fileTimer;
    QTimer m_dirTimer;
    int m_bufferDuration;

    QHash<QString, Audio *> m_audios;
    QHash<qint64, Audio *> m_sizes;
    QSet<QString> m_dirs;
};

#endif // FILESYSTEMWATCHER_HPP
