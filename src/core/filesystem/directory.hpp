#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

#include <QHash>
#include <QObject>
#include <QSet>

#include "types.hpp"

class Directory : public QObject
{
    Q_OBJECT

public:
    explicit Directory(QObject *parent = nullptr);
    explicit Directory(const Path &path, QObject *parent = nullptr);

    Path path() const;
    QSet<File> files() const;
    QHash<Path, Directory *> dirs() const;

    bool exists() const;

    void parse();

    Files globAudios(bool recursive = true) const;
    Files processChanges();

signals:
    void parsed(Directory *dir);
    void created(Directory *dir);
    void removed(Directory *dir);

private:
    void processRemovedDirChanges(Files &changes);
    void processExistingDirChanges(Files &changes);
    void processFileChanges(Files &changes);

    Path m_path;
    QSet<File> m_files;
    QHash<Path, Directory *> m_dirs;
};

#endif // DIRECTORY_HPP