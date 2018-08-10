#ifndef FILESYSTEMWATCHER_HPP
#define FILESYSTEMWATCHER_HPP

#include "audio.hpp"
#include "types.hpp"

#include <QFileInfo>
#include <QFileSystemWatcher>
#include <QHash>
#include <QObject>

class FileSystemWatcher : public QObject
{
    Q_OBJECT

public:
    FileSystemWatcher(QObject *parent = nullptr);
    ~FileSystemWatcher();

    static Files globFiles(const QString &path, const QString &filter, bool recursive = true);
    static Files globAudios(const QString &path, bool recursive = true);
    static Paths globDirs(const QString &path, bool recursive = true);

    void watch(Audio *audio);

signals:
    void added(const QString &file);
    void removed(Audio *audio);
    void modified(Audio *audio);
    void renamed(Audio *audio, const QString &file);

private slots:
    void onWatcherFileChanged(const QString &file);
    void onWatcherDirectoryChanged(const QString &directory);

private:
    void emitAdded(const QString &file);
    void emitRemoved(Audio *audio);
    void emitModified(Audio *audio);
    void emitRenamed(Audio *audio, const QString &file);

    int dirCount(const QString &dir);

    QFileSystemWatcher m_watcher;
    QHash<QString, Audio *> m_audios;
    QHash<qint64, Audio *> m_sizes;
    QHash<QString, int> m_dirs;
};

#endif // FILESYSTEMWATCHER_HPP
