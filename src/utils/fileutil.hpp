#ifndef FILEUTIL_HPP
#define FILEUTIL_HPP

#include <QDir>
#include <QStringList>
#include <QTextStream>

#include "logger.hpp"

class FileUtil
{
public:
    static QString read(const QString &path);
    static bool exists(const QString &path);
    static QDir dir(const QString &path);
    static QStringList glob(const QString &path, const QString &pattern, bool recursive = true);
    static QString fileName(const QString &file);
};

#endif // FILEUTIL_HPP
