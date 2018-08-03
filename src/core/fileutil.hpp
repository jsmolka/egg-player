#ifndef FILEUTIL_HPP
#define FILEUTIL_HPP

#include <QDateTime>
#include <QDirIterator>
#include <QTextStream>

#include "types.hpp"

namespace FileUtil
{
    extern bool exists(const QString &file);
    extern QString fileName(const QString &file);
    extern qint64 created(const QString &file);
    extern qint64 modified(const QString &file);

    extern QString read(const QString &file, const QString &defaultValue = QString());
    extern QByteArray readBytes(const QString &file, const QByteArray &defaultValue = QByteArray());

    extern void write(const QString &file, const QString &content);
    extern void write(const QString &file, const QByteArray &content);

    extern Files glob(const QString &path, const QString &filter);
}

#endif // FILEUTIL_HPP
