#include "utils.hpp"

#include <QFile>
#include <QTextStream>

const wchar_t *Util::toWString(const QString &string)
{
    return reinterpret_cast<const wchar_t *>(string.constData());
}

QString Util::toQString(const TagLib::String &string)
{
    return QString::fromWCharArray(string.toCWString(), static_cast<int>(string.size()));
}

QString Util::toQString(const TagLib::FileName &string)
{
    return QString::fromWCharArray(static_cast<const wchar_t *>(string));
}

QString FileUtil::read(const QString &file, const QString &defaultValue)
{
    QFile qFile(file);
    if (!qFile.open(QFile::ReadOnly))
        return defaultValue;

    return QTextStream(&qFile).readAll();
}

QByteArray FileUtil::readBytes(const QString &file, const QByteArray &defaultValue)
{
    QFile qFile(file);
    if (!qFile.open(QFile::ReadOnly))
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
