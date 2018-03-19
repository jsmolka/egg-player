#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
#include <QStringList>
#include <QTextStream>

class FileUtil
{
public:
    static QString read(QString path);
    static bool exists(QString path);
    static QDir dir(QString path);
    static QString join(QDir dir, QString path);
    static QString join(QString path1, QString path2);
    static QStringList glob(QString &path, QString pattern, bool recursive = true);
};

#endif // FILEUTIL_H
