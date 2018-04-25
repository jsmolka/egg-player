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

/*
 * The Cache class is responsible for caching and later
 * loading all audio covers. This is necessary because loading
 * the cover while playing the song is not possible.
 */
class Cache
{
public:
    Cache();
    ~Cache();

    bool insert(Audio *audio, int size = 200);
    bool contains(Audio *audio);
    QPixmap cover(const QString &path, int size);

private:
    QSqlDatabase db();

    int lastCoverId();
    int coverId(const QByteArray &bytes);
    int insertCover(const QByteArray &bytes);

    void handleError(const QSqlQuery &query);

    QString lastQuery(const QSqlQuery &query);
    QByteArray coverToBytes(const QPixmap &cover);
    QPixmap resize(const QPixmap &pixmap, int size);
};

#endif // CACHE_HPP
