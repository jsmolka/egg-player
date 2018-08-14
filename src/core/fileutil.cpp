#include "fileutil.hpp"

bool FileUtil::exists(const QString &file)
{
    return QFileInfo(file).exists();
}

QString FileUtil::fileName(const QString &file)
{
    return QFileInfo(file).baseName();
}

qint64 FileUtil::modified(const QString &file)
{
    return QFileInfo(file).lastModified().toSecsSinceEpoch();
}

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
