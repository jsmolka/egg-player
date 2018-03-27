#ifndef CACHE_HPP
#define CACHE_HPP

#include <QBuffer>
#include <QByteArray>
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

    bool connect();
    void close();
    bool insert(QString artist, QString album, QPixmap cover);
    bool exists(QString artist, QString album);
    QPixmap cover(QString artist, QString album, int size);

private:
    QPixmap scale(QPixmap pixmap, int size);

    QSqlDatabase m_db;
    QSqlQuery m_query;

};

#endif // CACHE_HPP
