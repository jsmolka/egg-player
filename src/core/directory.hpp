#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

#include <QDirIterator>
#include <QObject>
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

    Files files() const;
    DirectoryVector dirs() const;

    void parse();

signals:
    void parsed(Directory *dir);

private:
    Path m_path;
    Files m_files;
    DirectoryVector m_dirs;
};

#endif // DIRECTORY_HPP
