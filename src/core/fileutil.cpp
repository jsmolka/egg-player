#include "fileutil.hpp"

#include <QFile>
#include <QTextStream>

QString FileUtil::read(const File &file, const QString &defaultValue)
{
    QFile qFile(file);
    if (!qFile.open(QFile::ReadOnly))
        return defaultValue;

    return QTextStream(&qFile).readAll();
}

QByteArray FileUtil::readBytes(const File &file, const QByteArray &defaultValue)
{
    QFile qFile(file);
    if (!qFile.open(QFile::ReadOnly))
        return defaultValue;

    return qFile.readAll();
}

void FileUtil::write(const File &file, const QString &content)
{
    QFile qFile(file);
    if (!qFile.open(QFile::WriteOnly))
        return;

    QTextStream(&qFile) << content;
}

void FileUtil::write(const File &file, const QByteArray &content)
{
    QFile qFile(file);
    if (!qFile.open(QFile::WriteOnly))
        return;

    qFile.write(content);
}
