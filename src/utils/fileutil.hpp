#ifndef FILEUTIL_HPP
#define FILEUTIL_HPP

#include <QDir>
#include <QStringList>
#include <QTextStream>

class FileUtil
{
public:
    static QString read(const QString &path);
    static bool exists(const QString &path);
    static QDir dir(const QString &path);
    static QString join(const QDir &dir, const QString &path);
    static QString join(const QString &path1, const QString &path2);
    static QStringList glob(const QString &path, const QString &pattern, bool recursive = true);
    static QString fileName(const QString &file, bool ext = false);
};

#endif // FILEUTIL_HPP
