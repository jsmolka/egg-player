#ifndef CACHE_HPP
#define CACHE_HPP

#include <QBuffer>
#include <QPixmap>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "audio.hpp"
#include "constants.hpp"
#include "logger.hpp"

class Cache
{
public:
    Cache();
    ~Cache();

    bool connect();
    void close();
    bool insert(Audio *audio, int size = 200);
    bool exists(Audio *audio);
    QPixmap cover(const QString &path, int size);

private:
    int lastCoverId();
    int coverId(const QByteArray &bytes);
    int insertCover(const QByteArray &bytes);

    void handleError(const QSqlQuery &query);

    QString lastQuery(const QSqlQuery &query);
    QByteArray coverToBytes(const QPixmap &cover);
    QPixmap scale(const QPixmap &pixmap, int size);

    QSqlDatabase m_db;
};

#endif // CACHE_HPP
