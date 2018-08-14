#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <QHash>
#include <QHashIterator>
#include <QObject>

#include "audio.hpp"
#include "directory.hpp"
#include "types.hpp"

class FileSystem : public QObject
{
public:
    FileSystem(QObject *parent = nullptr);
    ~FileSystem();

    QHash<Path, Directory *> dirs() const;

    void addPath(const Path &path);

    Files globAudios() const;

private slots:
    void onDirParsed(Directory *dir);

private:
    QHash<Path, Directory *> m_dirs;
};

#endif // FILESYSTEM_HPP
