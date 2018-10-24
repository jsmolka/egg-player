#ifndef UNIQUEFILEINFO_HPP
#define UNIQUEFILEINFO_HPP

#include <QHashFunctions>

#include "core/globals.hpp"

class UniqueFileInfo
{
public:
    UniqueFileInfo();
    explicit UniqueFileInfo(const QString &file);

    quint64 index() const;
    quint64 volume() const;

private:
    void readInfo(const QString &file);

    quint64 m_index;
    quint64 m_volume;
};

inline bool operator==(const UniqueFileInfo &info1, const UniqueFileInfo &info2)
{
    return info1.index() == info2.index() && info1.volume() == info2.volume();
}

inline uint qHash(const UniqueFileInfo &key, uint seed)
{
    return qHash(key.index() ^ key.volume(), seed);
}

#endif // UNIQUEFILEINFO_HPP
