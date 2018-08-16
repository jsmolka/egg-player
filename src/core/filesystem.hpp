#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <Windows.h>

#include <QHash>
#include <QHashIterator>
#include <QObject>

#include "audio.hpp"
#include "bimap.hpp"
#include "directory.hpp"
#include "filesystemwatcher.hpp"
#include "logger.hpp"
#include "types.hpp"

struct UniqueInfo
{
    UniqueInfo(DWORD volume = 0, DWORD low = 0, DWORD high = 0)
        : volume(volume), low(low), high(high) {}

    bool operator==(const UniqueInfo &info) const
    {
        return volume == info.volume && low == info.low && high == info.high;
    }

    DWORD volume;
    DWORD low;
    DWORD high;
};

class FileSystem : public QObject
{
    Q_OBJECT

public:
    FileSystem(QObject *parent = nullptr);
    ~FileSystem();

    QHash<Path, Directory *> dirs() const;

    void addPath(const Path &path);

    Files globAudios() const;

public: // Make signals in future
    void eventModified(const File &file);

private slots:
    void onDirParsed(Directory *dir);

    void onFileChanged(const File &file);
    void onDirectoryChanged(const Path &dir);

private:
    UniqueInfo uniqueInfo(const File &file);

    Bimap<Path, UniqueInfo> m_unique;
    QHash<Path, Directory *> m_dirs;
    FileSystemWatcher m_watcher;
};

#endif // FILESYSTEM_HPP
