#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

#include <QDirIterator>
#include <QHash>
#include <QHashIterator>
#include <QObject>
#include <QMutableSetIterator>
#include <QSet>

#include "types.hpp"

class Directory : public QObject
{
    Q_OBJECT

public:
    Directory(QObject *parent = nullptr);
    Directory(const Path &path, QObject *parent = nullptr);
    ~Directory();

    void setPath(const Path &path);
    Path path() const;

    QSet<File> files() const;
    QHash<Path, Directory *> dirs() const;

    bool exists() const;

    void parse();

    Files processChanges();

signals:
    void parsed(Directory *dir);
    void created(Directory *dir);
    void removed(Directory *dir);

private:
    void processDirChanges(Files &changes);
    void processFileChanges(Files &changes);

    Path m_path;
    QSet<File> m_files;
    QHash<Path, Directory *> m_dirs;
};

#endif // DIRECTORY_HPP
