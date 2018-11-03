#ifndef UTILS_HPP
#define UTILS_HPP

#include <QFile>
#include <QString>
#include <QTextStream>

#include <taglib/fileref.h>

namespace Util
{
    inline const wchar_t *toWString(const QString &string)
    {
        return reinterpret_cast<const wchar_t *>(string.constData());
    }

    inline QString toQString(const TagLib::String &string)
    {
        return QString::fromWCharArray(string.toCWString(), static_cast<int>(string.size()));
    }

    inline QString toQString(const TagLib::FileName &string)
    {
        return QString::fromWCharArray(static_cast<const wchar_t *>(string));
    }
}

namespace FileUtil
{
    inline QString read(const QString &file, const QString &defaultValue = QString())
    {
        QFile qFile(file);
        if (!qFile.open(QFile::ReadOnly))
            return defaultValue;

        return QTextStream(&qFile).readAll();
    }

    inline QByteArray readBytes(const QString &file, const QByteArray &defaultValue = QByteArray())
    {
        QFile qFile(file);
        if (!qFile.open(QFile::ReadOnly))
            return defaultValue;

        return qFile.readAll();
    }

    inline void write(const QString &file, const QString &content)
    {
        QFile qFile(file);
        if (!qFile.open(QFile::WriteOnly))
            return;

        QTextStream(&qFile) << content;
    }

    inline void write(const QString &file, const QByteArray &content)
    {
        QFile qFile(file);
        if (!qFile.open(QFile::WriteOnly))
            return;

        qFile.write(content);
    }
}

#endif // UTILS_HPP
