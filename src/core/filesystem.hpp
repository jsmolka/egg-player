#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <QHash>
#include <QObject>

#include "audio.hpp"
#include "bimap.hpp"
#include "directory.hpp"
#include "filesystemwatcher.hpp"
#include "types.hpp"
#include "uniquefileinfo.hpp"

class FileSystem : public QObject
{
    Q_OBJECT

public:
    explicit FileSystem(QObject *parent = nullptr);

    Bimap<File, UniqueFileInfo> uniqueInfo() const;
    QHash<Path, Directory *> dirs() const;
    QHash<File, Audio *> audios() const;
    FileSystemWatcher &watcher();

    void addPath(const Path &path);

    Files globAudios() const;

    void watchAudio(Audio *audio);
    void unwatchAudio(Audio *audio);

signals:
    void modified(Audio *audio);
    void renamed(Audio *audio, const File &to);
    void added(const File &file);
    void removed(Audio *audio);

private slots:
    void onDirParsed(Directory *dir);
    void onDirCreated(Directory *dir);
    void onDirRemoved(Directory *dir);

    void onFileChanged(const File &file);
    void onDirectoryChanged(const Path &dir);

private:
    void eventModified(const File &file);
    void eventRenamed(const File &from, const File &to);
    void eventAdded(const File &file);
    void eventRemoved(const File &file);

    Bimap<File, UniqueFileInfo> m_unique;
    QHash<Path, Directory *> m_dirs;
    QHash<File, Audio *> m_audios;
    FileSystemWatcher m_watcher;
};

#endif // FILESYSTEM_HPP
