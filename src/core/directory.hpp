#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

#include <QDirIterator>
#include <QObject>
#include <QSet>
#include <QVector>

#include "types.hpp"

class Directory;

using DirectoryVector = QVector<Directory *>;

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
    DirectoryVector dirs() const;

    void parse();

    Files processChanges();

signals:
    void parsed(Directory *dir);

private:
    Path m_path;
    QSet<File> m_files;
    DirectoryVector m_dirs;
};

#endif // DIRECTORY_HPP
