#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

class FileUtil
{
public:
    static QString read(QString path);
    static bool exists(QString path);
    static QDir dir(QString path);
    static QString join(QDir dir, QString path);
    static QString join(QString path1, QString path2);
};

#endif // FILEUTIL_H
