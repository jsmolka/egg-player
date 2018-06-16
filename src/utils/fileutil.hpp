#ifndef FILEUTIL_HPP
#define FILEUTIL_HPP

#include <QDirIterator>
#include <QTextStream>

#include "types.hpp"


namespace FileUtil
{
    extern bool exists(const QString &file);
    extern QString fileName(const QString &file);
    extern quint64 size(const QString &file);
    extern QString read(const QString &file);
    extern StringList glob(const QString &path, const QString &suffix);
}

#endif // FILEUTIL_HPP
