#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <Windows.h>

#include <QHash>
#include <QHashIterator>
#include <QObject>
#include <QSet>

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

    DWORD volume;
    DWORD low;
    DWORD high;
};

inline bool operator==(const UniqueInfo &info1, const UniqueInfo &info2)
{
    return info1.volume == info2.volume
            && info1.low == info2.low
            && info1.high == info2.high;
}

inline uint qHash(const UniqueInfo &key, uint seed)
{
    return qHash(key.volume ^ key.low ^ key.high, seed);
}

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
    void eventRenamed(const File &from, const File &to);
    void eventAdded(const File &file);
    void eventRemoved(const File &file);

private slots:
    void onDirParsed(Directory *dir);
    void onDirCreated(Directory *dir);
    void onDirRemoved(Directory *dir);

    void onFileChanged(const File &file);
    void onDirectoryChanged(const Path &dir);

private:
    UniqueInfo uniqueInfo(const File &file);

    Bimap<File, UniqueInfo> m_unique;
    QHash<Path, Directory *> m_dirs;
    FileSystemWatcher m_watcher;
};

#endif // FILESYSTEM_HPP
