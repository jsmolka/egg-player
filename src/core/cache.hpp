#ifndef CACHE_HPP
#define CACHE_HPP

#include <QBuffer>
#include <QByteArray>
#include <QPixmap>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

#include "src/constants/database.hpp"

class Cache
{
public:
    Cache();

    bool connect();
    void close();
    bool insert(QString file, QPixmap cover);
    bool exists(QString file);
    QPixmap cover(QString file, int size);

private:
    QSqlDatabase m_db;
    QSqlQuery m_query;

};

#endif // CACHE_HPP
