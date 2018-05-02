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

    bool insert(Audio *audio, int size = 200);
    bool contains(Audio *audio);
    QPixmap cover(const QString &path, int size = 200);
    QPixmap cover(Audio *audio, int size = 200);

private:
    QSqlDatabase db();

    void createCovers();
    void createAudios();

    int getOrInsertCover(const QPixmap &cover);
    int insertCover(const QByteArray &bytes);

    int coverId(const QByteArray &bytes);
    int lastCoverId();

    int queryCoverIdByLength(int length);
    int queryCoverIdByBlob(const QByteArray &bytes);

    void handleError(const QSqlQuery &query);

    QString lastQuery(const QSqlQuery &query);
    QByteArray coverToBytes(const QPixmap &cover);
};

#endif // CACHE_HPP
