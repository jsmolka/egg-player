#ifndef UNIQUEFILEINFO_HPP
#define UNIQUEFILEINFO_HPP

#include <QHashFunctions>

class UniqueFileInfo
{
public:
    UniqueFileInfo();
    explicit UniqueFileInfo(const QString &file);

    QString file() const;
    quint64 index() const;
    quint64 volume() const;

    bool isValid() const;

private:
    void readFileInfo();

    QString m_file;
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
