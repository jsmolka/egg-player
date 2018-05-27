#ifndef CACHE_HPP
#define CACHE_HPP

#include <QBuffer>
#include <QHash>
#include <QPixmap>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QThread>

#include "audio.hpp"
#include "constants.hpp"
#include "logger.hpp"

class Cache
{
public:
    Cache();
    ~Cache();

    Audio * load(const QString &path);

    bool insertAudio(Audio *audio);
    bool insertCover(Audio *audio, int size = 200);

    bool contains(Audio *audio);
    QPixmap cover(Audio *audio, int size = 200);

private:
    QString dbName();
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

    static QHash<int, QPixmap> _covers;
};

#endif // CACHE_HPP
