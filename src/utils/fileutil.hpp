#ifndef FILEUTIL_HPP
#define FILEUTIL_HPP

#include <QDirIterator>
#include <QTextStream>

#include "types.hpp"

class FileUtil
{
public:
    static QString read(const QString &file);
    static bool exists(const QString &path);
    static QString fileName(const QString &file);
    static StringList glob(const QString &path, const QString &suffix);
};

#endif // FILEUTIL_HPP
