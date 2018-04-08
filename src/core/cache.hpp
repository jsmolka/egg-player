#ifndef CACHE_HPP
#define CACHE_HPP

#include <QBuffer>
#include <QPixmap>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "audio.hpp"
#include "constant.hpp"

class Cache
{
public:
    Cache();
    ~Cache();

    bool connect();
    void close();
    bool insert(Audio *audio);
    bool exists(Audio *audio);
    QPixmap cover(const QString &path, int size);

private:
    int lastCoverId();
    QByteArray coverToBytes(const QPixmap &cover);
    int coverId(const QByteArray &bytes);
    int insertCover(const QByteArray &bytes);
    QPixmap scale(const QPixmap &pixmap, int size);

    QSqlDatabase m_db;
};

#endif // CACHE_HPP
