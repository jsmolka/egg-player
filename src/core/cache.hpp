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

    Audio * loadAudio(const QString &path);

    void insertAudio(Audio *audio);
    void updateAudio(Audio *audio);

    int insertCover(const QPixmap &cover);
    void setAudioCoverId(Audio *audio, int id);

    QPixmap cover(Audio *audio, int size = 200);

private:
    QString dbName();
    QSqlDatabase db();

    void createCovers();
    void createAudios();
    void createTables();

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

    static bool _created;
};

#endif // CACHE_HPP
