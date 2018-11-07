#ifndef UTILS_HPP
#define UTILS_HPP

#include <QString>

#include <taglib/fileref.h>

class Util
{
public:
    static const wchar_t *toWString(const QString &string);
    static QString toQString(const TagLib::String &string);
    static QString toQString(const TagLib::FileName &string);
};

class FileUtil
{
public:
    static QString read(const QString &file, const QString &defaultValue = QString());
    static QByteArray readBytes(const QString &file, const QByteArray &defaultValue = QByteArray());

    static void write(const QString &file, const QString &content);
    static void write(const QString &file, const QByteArray &content);
};

#endif // UTILS_HPP
