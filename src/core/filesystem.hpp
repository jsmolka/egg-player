#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <QHash>
#include <QObject>

#include "core/audio.hpp"
#include "core/bimap.hpp"
#include "core/types.hpp"
#include "core/filesystem/directory.hpp"
#include "core/filesystem/filesystemwatcher.hpp"
#include "core/filesystem/uniquefileinfo.hpp"

class FileSystem : public QObject
{
    Q_OBJECT

public:
    explicit FileSystem(QObject *parent = nullptr);

    Bimap<QString, fs::UniqueFileInfo> uniqueInfo() const;
    QHash<QString, fs::Directory *> dirs() const;
    QHash<QString, Audio *> audios() const;

    const fs::FileSystemWatcher &watcher() const;

    fs::FileSystemWatcher &watcher();

    void addPath(const QString &path);

    QStrings globFiles() const;

    void watchAudio(Audio *audio);
    void unwatchAudio(Audio *audio);

signals:
    void modified(Audio *audio);
    void renamed(Audio *audio, const QString &to);
    void added(const QStrings &files);
    void removed(Audio *audio);

private slots:
    void onDirParsed(fs::Directory *dir);
    void onDirCreated(fs::Directory *dir);
    void onDirRemoved(fs::Directory *dir);

    void onFileChanged(const QString &file);
    void onDirectoryChanged(const QString &path);

private:
    using InfoHash = QHash<fs::UniqueFileInfo, QString>;

    void processChanges(const QStrings &changes, InfoHash &oldInfos, InfoHash &newInfos);
    void triggerEvents(InfoHash &oldInfos, InfoHash &newInfos);

    void processModified(const QString &file);
    void processRenamed(const QString &from, const QString &to);
    void processAdded(const QString &file, const fs::UniqueFileInfo &info);
    void processRemoved(const QString &file);

    Bimap<QString, fs::UniqueFileInfo> m_unique;
    QHash<QString, fs::Directory *> m_dirs;
    QHash<QString, Audio *> m_audios;
    fs::FileSystemWatcher m_watcher;
};

#endif // FILESYSTEM_HPP
