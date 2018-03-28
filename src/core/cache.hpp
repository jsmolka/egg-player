#ifndef CACHE_HPP
#define CACHE_HPP

#include <QBuffer>
#include <QPixmap>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

#include "src/constants/constant.hpp"
#include "src/constants/database.hpp"

class Cache
{
public:
    Cache();
    ~Cache();

    bool connect();
    void close();
    bool insert(const QString &artist, const QString &album, const QPixmap &cover);
    bool exists(const QString &artist, const QString &album);
    QPixmap cover(const QString &artist, const QString &album, int size);

private:
    QPixmap scale(QPixmap pixmap, int size);

    QSqlDatabase m_db;

};

#endif // CACHE_HPP
