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
#include "util.hpp"

class Cache
{
public:
    Cache();
    ~Cache();

    bool transaction();
    bool commit();
    bool rollback();

    Audio * load(const QString &path);

    void insertTags(Audio *audio);
    int insertCover(Audio *audio, int size = 200);
    void updateTags(Audio *audio);

    int coverId(Audio *audio);
    QPixmap cover(Audio *audio, int size = 200);

private:
    QString dbName();
    QSqlDatabase db();

    void createCovers();
    void createAudios();
    int getOrInsertCover(const QPixmap &cover);
    int insertByteCover(const QByteArray &bytes);

    int coverId(const QByteArray &bytes);
    int lastCoverId();
    int queryCoverIdBySize(int size);
    int queryCoverIdByBlob(const QByteArray &bytes);

    void handleError();

    QString lastQuery();

    QByteArray coverToBytes(const QPixmap &cover);

    QSqlDatabase m_db;
    QSqlQuery m_query;

    static QHash<int, QPixmap> _covers;
};

#endif // CACHE_HPP
