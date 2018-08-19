#include "fileutil.hpp"

QString FileUtil::read(const QString &file, const QString &defaultValue)
{
    QFile qFile(file);
    if (!qFile.open(QFile::ReadOnly | QFile::Text))
        return defaultValue;

    return QTextStream(&qFile).readAll();
}

QByteArray FileUtil::readBytes(const QString &file, const QByteArray &defaultValue)
{
    QFile qFile(file);
    if (!qFile.open(QFile::ReadOnly | QFile::Text))
        return defaultValue;

    return qFile.readAll();
}

void FileUtil::write(const QString &file, const QString &content)
{
    QFile qFile(file);
    if (!qFile.open(QFile::WriteOnly))
        return;

    QTextStream(&qFile) << content;
}

void FileUtil::write(const QString &file, const QByteArray &content)
{
    QFile qFile(file);
    if (!qFile.open(QFile::WriteOnly))
        return;

    qFile.write(content);
}
