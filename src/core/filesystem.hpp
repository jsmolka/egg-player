#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <QHash>
#include <QObject>

#include "core/audio.hpp"
#include "core/bimap.hpp"
#include "core/filesystem/directory.hpp"
#include "core/filesystem/filesystemwatcher.hpp"
#include "core/filesystem/uniquefileinfo.hpp"

class FileSystem : public QObject
{
    Q_OBJECT

public:
    explicit FileSystem(QObject *parent = nullptr);

    Bimap<QString, UniqueFileInfo> uniqueInfo() const;
    QHash<QString, Directory *> dirs() const;
    QHash<QString, Audio *> audios() const;

    const FileSystemWatcher &watcher() const;

    FileSystemWatcher &watcher();

    void addPath(const QString &path);

    QStrings globFiles() const;

    void watchAudio(Audio *audio);
    void unwatchAudio(Audio *audio);

signals:
    void modified(Audio *audio);
    void renamed(Audio *audio, const QString &to);
    void added(const QString &file);
    void removed(Audio *audio);

private slots:
    void onDirParsed(Directory *dir);
    void onDirCreated(Directory *dir);
    void onDirRemoved(Directory *dir);

    void onFileChanged(const QString &file);
    void onDirectoryChanged(const QString &path);

private:
    using InfoHash = QHash<UniqueFileInfo, QString>;

    void processChanges(const QStrings &changes, InfoHash &oldInfos, InfoHash &newInfos);
    void triggerEvents(InfoHash &oldInfos, InfoHash &newInfos);

    void eventModified(const QString &file);
    void eventRenamed(const QString &from, const QString &to);
    void eventAdded(const QString &file, const UniqueFileInfo &info);
    void eventRemoved(const QString &file);

    Bimap<QString, UniqueFileInfo> m_unique;
    QHash<QString, Directory *> m_dirs;
    QHash<QString, Audio *> m_audios;
    FileSystemWatcher m_watcher;
};

#endif // FILESYSTEM_HPP
