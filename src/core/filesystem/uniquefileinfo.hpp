#ifndef UNIQUEFILEINFO_HPP
#define UNIQUEFILEINFO_HPP

#include <QHashFunctions>

#include "core/macros.hpp"

class UniqueFileInfo
{
public:
    UniqueFileInfo();
    explicit UniqueFileInfo(const QString &file);

    EGG_PPROP(quint64, index, setIndex, index)
    EGG_PPROP(quint64, volume, setVolume, volume)

    bool isValid() const;

private:
    void readInfo(const QString &file);
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
