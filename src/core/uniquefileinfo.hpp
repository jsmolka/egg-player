#ifndef UNIQUEFILEINFO_HPP
#define UNIQUEFILEINFO_HPP

#include <Windows.h>

#include <QHashFunctions>

#include "types.hpp"

class UniqueFileInfo
{
public:
    UniqueFileInfo();
    explicit UniqueFileInfo(const File &file);
    ~UniqueFileInfo();

    void setLow(DWORD low);
    DWORD low() const;

    void setHigh(DWORD high);
    DWORD high() const;

    void setVolume(DWORD volume);
    DWORD volume() const;

private:
    void readInfo(const File &file);

    DWORD m_low;
    DWORD m_high;
    DWORD m_volume;
};

inline bool operator==(const UniqueFileInfo &info1, const UniqueFileInfo &info2)
{
    return info1.low() == info2.low()
            && info1.high() == info2.high()
            && info1.volume() == info2.volume();
}

inline uint qHash(const UniqueFileInfo &key, uint seed)
{
    return qHash(key.volume() ^ key.low() ^ key.high(), seed);
}

#endif // UNIQUEFILEINFO_HPP
