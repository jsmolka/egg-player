#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <QHash>
#include <QHashIterator>
#include <QObject>

#include "audio.hpp"
#include "directory.hpp"
#include "filesystemwatcher.hpp"
#include "types.hpp"

class FileSystem : public QObject
{
    Q_OBJECT

public:
    FileSystem(QObject *parent = nullptr);
    ~FileSystem();

    QHash<Path, Directory *> dirs() const;

    void addPath(const Path &path);

    Files globAudios() const;

private slots:
    void onDirParsed(Directory *dir);

    void onFileChanged(const File &file);
    void onDirectoryChanged(const Path &dir);

private:
    QHash<Path, Directory *> m_dirs;
    FileSystemWatcher m_watcher;
};

#endif // FILESYSTEM_HPP
