#ifndef FILEUTIL_HPP
#define FILEUTIL_HPP

#include <QDirIterator>
#include <QTextStream>

#include "constants.hpp"
#include "config.hpp"
#include "types.hpp"

namespace FileUtil
{
    extern bool exists(const QString &file);
    extern QString fileName(const QString &file);
    extern quint64 size(const QString &file);
    extern QString read(const QString &file);
    extern Files glob(const QString &path, const QString &suffix);

    namespace Css
    {
        extern QString bar();
        extern QString egg();
        extern QString library();
    }
}

#endif // FILEUTIL_HPP
