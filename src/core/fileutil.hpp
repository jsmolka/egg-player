#ifndef FILEUTIL_HPP
#define FILEUTIL_HPP

#include <QDateTime>
#include <QDirIterator>
#include <QTextStream>

#include "types.hpp"

namespace FileUtil
{
    extern QString read(const QString &file, const QString &defaultValue = QString());
    extern QByteArray readBytes(const QString &file, const QByteArray &defaultValue = QByteArray());

    extern void write(const QString &file, const QString &content);
    extern void write(const QString &file, const QByteArray &content);
}

#endif // FILEUTIL_HPP
