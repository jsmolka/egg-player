#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QDebug>
#include <QFile>
#include <QTextStream>

class FileUtil
{
public:
    FileUtil();

    static QString read(QString path);
};

#endif // FILEUTIL_H
