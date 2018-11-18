#ifndef FILESYSTEM2_HPP
#define FILESYSTEM2_HPP

#include <QHash>
#include <QObject>
#include <QSet>

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
    enum GlobPolicy {Recursive, Shallow};

    explicit FileSystem(QObject *parent = nullptr);

    void addPath(const QString &path);
    void addFile(const QString &file);

    QStrings globFiles() const;
    QStrings globDirFiles(const QString &path, GlobPolicy policy = Shallow) const;

    void watchAudio(Audio *audio);
    void unwatchAudio(Audio *audio);

    bool containsFile(const QString &file) const;
    bool containsDir(const QString &dir) const;

    bool isIgnored(const QString &file) const;

signals:
    void added(const QStrings &files);
    void removed(Audio *audio);
    void modified(Audio *audio);
    void renamed(Audio *audio, const QString &name);

private slots:
    void onDirAdded(fs::Directory *dir);
    void onDirRemoved(fs::Directory *dir);

    void onFileChanged(const QString &file);
    void onDirChanged(const QString &path);

private:
    void addDir(fs::Directory *dir);

    QStrings globDirFiles(fs::Directory *dir, GlobPolicy policy) const;
    void ignoreDirFiles(fs::Directory *dir);
    void ignoreDirAdds(fs::Directory *dir);

    void processAdded(const QString &file, const fs::UniqueFileInfo &info);
    void processRemoved(const QString &file);
    void processModified(const QString &file);
    void processRenamed(const QString &from, const QString &to);

    Bimap<QString, fs::UniqueFileInfo> m_unique;
    QHash<QString, fs::Directory *> m_dirs;
    QHash<QString, Audio *> m_watched;
    fs::FileSystemWatcher m_watcher;
    QSet<QString> m_ignored;
};

#endif // FILESYSTEM2_HPP
