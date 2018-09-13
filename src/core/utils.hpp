#ifndef UTILS_HPP
#define UTILS_HPP

#include <QString>

#include <taglib/fileref.h>

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

#endif // UTILS_HPP
