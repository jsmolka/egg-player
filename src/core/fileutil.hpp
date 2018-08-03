#ifndef FILEUTIL_HPP
#define FILEUTIL_HPP

#include <QDateTime>
#include <QDirIterator>
#include <QTextStream>

#include "types.hpp"

namespace FileUtil
{
    inline bool exists(const QString &file)
    {
        return QFileInfo(file).exists();
    }

    inline QString fileName(const QString &file)
    {
        return QFileInfo(file).baseName();
    }

    inline qint64 created(const QString &file)
    {
        return QFileInfo(file).created().toSecsSinceEpoch();
    }

    inline qint64 modified(const QString &file)
    {
        return QFileInfo(file).lastModified().toSecsSinceEpoch();
    }

    inline QString read(const QString &file, const QString &defaultValue = QString())
    {
        QFile qFile(file);
        if (!qFile.open(QFile::ReadOnly | QFile::Text))
            return defaultValue;

        return QTextStream(&qFile).readAll();
    }

    inline QByteArray readBytes(const QString &file, const QByteArray &defaultValue = QByteArray())
    {
        QFile qFile(file);
        if (!qFile.open(QFile::ReadOnly | QFile::Text))
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

    inline Files glob(const QString &path, const QString &filter)
    {
        Files result;

        QDirIterator iterator(path, QStringList() << filter, QDir::Files, QDirIterator::Subdirectories);
        while (iterator.hasNext())
        {
            iterator.next();
            result << iterator.filePath();
        }
        return result;
    }
}

#endif // FILEUTIL_HPP
