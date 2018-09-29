#ifndef CACHE_HPP
#define CACHE_HPP

#include <QBuffer>
#include <QPixmap>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "audio.hpp"

class Cache
{
public:
    Cache();

    bool transaction();
    bool commit();
    bool rollback();

    void initialize();

    Audio *loadAudio(const QString &file);
    void insertAudio(Audio *audio);
    void updateAudio(Audio *audio, const QString &newFile = QString());

    int insertCover(const QPixmap &cover);
    void updateCover(const QPixmap &cover);
    void setAudioCoverId(Audio *audio, int id);
    void updateAudioCover(Audio *audio, const QPixmap &cover);

    QPixmap coverById(int id);

private:
    static QString dbName();
    static QSqlDatabase db();
    static QByteArray coverToBytes(const QPixmap &cover);

    void createCovers();
    void createAudios();
    bool defaultCoverExists();
    void insertDefaultCover();

    int insertByteCover(const QByteArray &bytes);
    void updateByteCover(int id, const QByteArray &bytes);

    int coverId(const QByteArray &bytes);
    int lastCoverId();
    int coverIdBySize(int size);
    int coverIdByBlob(const QByteArray &bytes);

    void error();

    QString lastQuery();

    QSqlDatabase m_db;
    QSqlQuery m_query;
};

#endif // CACHE_HPP
