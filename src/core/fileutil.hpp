#ifndef FILEUTIL_HPP
#define FILEUTIL_HPP

#include "types.hpp"

namespace FileUtil
{
    extern QString read(const File &file, const QString &defaultValue = QString());
    extern QByteArray readBytes(const File &file, const QByteArray &defaultValue = QByteArray());

    extern void write(const File &file, const QString &content);
    extern void write(const File &file, const QByteArray &content);
}

#endif // FILEUTIL_HPP
