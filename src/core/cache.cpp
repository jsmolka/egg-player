#include "cache.hpp"

#include <QDateTime>
#include <QFileInfo>
#include <QMutex>
#include <QMutexLocker>
#include <QSqlError>
#include <QThread>
#include <QVariant>

#include "constants.hpp"
#include "logger.hpp"

Cache::Cache()
{    
    if (!QSqlDatabase::contains(dbName()))
        QSqlDatabase::addDatabase("QSQLITE", dbName());

    m_db = db();
    m_query = QSqlQuery(m_db);
    m_query.setForwardOnly(true);
}

bool Cache::transaction()
{
    return m_db.transaction();
}

bool Cache::commit()
{
    return m_db.commit();
}

bool Cache::rollback()
{
    return m_db.rollback();
}

void Cache::createTables()
{
    createCovers();
    createAudios();
    insertDefaultCover();
}

Audio *Cache::loadAudio(const QString &path)
{
    m_query.prepare(
        "SELECT * FROM audios "
        "WHERE path = :path"
    );
    m_query.bindValue(":path", path);

    if (!m_query.exec())
        error();

    Audio *audio = nullptr;
    if (m_query.first())
    {
        audio = new Audio;
        audio->setValid(true);
        audio->setCached(true);
        audio->setFile(m_query.value(0).toString());
        audio->tag().setTitle(m_query.value(1).toString());
        audio->tag().setArtist(m_query.value(2).toString());
        audio->tag().setAlbum(m_query.value(3).toString());
        audio->tag().setGenre(m_query.value(4).toString());
        audio->tag().setYear(m_query.value(5).toInt());
        audio->tag().setTrack(m_query.value(6).toInt());
        audio->tag().setDuration(m_query.value(7).toInt());
        audio->duration().setSecs(m_query.value(7).toInt());
        audio->cover().setId(m_query.value(8).toInt());
        audio->setModified(m_query.value(9).toInt());
        audio->setOutdated(audio->modified() != QFileInfo(audio->file()).lastModified().toSecsSinceEpoch());
    }
    return audio;
}

void Cache::insertAudio(Audio *audio)
{
    m_query.prepare(
        "INSERT INTO audios VALUES ("
        " :path,"
        " :title,"
        " :artist,"
        " :album,"
        " :genre,"
        " :year,"
        " :track,"
        " :duration,"
        " :coverid,"
        " :modified"
        ")"
    );
    m_query.bindValue(":path", audio->tag().file());
    m_query.bindValue(":title", audio->tag().title());
    m_query.bindValue(":artist", audio->tag().artist());
    m_query.bindValue(":album", audio->tag().album());
    m_query.bindValue(":genre", audio->tag().genre());
    m_query.bindValue(":year", audio->tag().year());
    m_query.bindValue(":track", audio->tag().track());
    m_query.bindValue(":duration", audio->duration().secs());
    m_query.bindValue(":coverid", audio->cover().id());
    m_query.bindValue(":modified", audio->modified());

    if (!m_query.exec())
        error();

    audio->setCached(true);
}

void Cache::updateAudio(Audio *audio, const QString &newPath)
{
    m_query.prepare(
        "UPDATE audios SET"
        " path = :newpath,"
        " title = :title,"
        " artist = :artist,"
        " album = :album,"
        " genre = :genre,"
        " year = :year,"
        " track = :track,"
        " duration = :duration,"
        " coverid = :coverid,"
        " modified = :modified "
        "WHERE path = :path"
    );
    m_query.bindValue(":newpath", newPath.isNull() ? audio->tag().file() : newPath);
    m_query.bindValue(":title", audio->tag().title());
    m_query.bindValue(":artist", audio->tag().artist());
    m_query.bindValue(":album", audio->tag().album());
    m_query.bindValue(":genre", audio->tag().genre());
    m_query.bindValue(":year", audio->tag().year());
    m_query.bindValue(":track", audio->tag().track());
    m_query.bindValue(":duration", audio->duration().secs());
    m_query.bindValue(":coverid", audio->cover().id());
    m_query.bindValue(":modified", audio->modified());
    m_query.bindValue(":path", audio->tag().file());

    if (!m_query.exec())
        error();
}

int Cache::insertCover(const QPixmap &cover)
{
    const QByteArray bytes = coverToBytes(cover);

    int id = coverId(bytes);
    if (id == 0)
        id = insertByteCover(bytes);

    return id;
}

void Cache::updateCover(const QPixmap &cover)
{
    const QByteArray bytes = coverToBytes(cover);

    const int id = coverId(bytes);
    if (id > 0)
        updateByteCover(id, bytes);
}

void Cache::setAudioCoverId(Audio *audio, int id)
{
    m_query.prepare(
        "UPDATE audios SET"
        " coverid = :coverid "
        "WHERE path = :path"
    );
    m_query.bindValue(":path", audio->tag().file());
    m_query.bindValue(":coverid", id);

    if (!m_query.exec())
        error();

    audio->cover().setId(id);
}

void Cache::updateAudioCover(Audio *audio, const QPixmap &cover)
{
    const int id = insertCover(cover);
    if (id > 0)
        setAudioCoverId(audio, id);
}

QPixmap Cache::coverById(int id)
{
    m_query.prepare(
        "SELECT cover FROM covers "
        "WHERE id = :id"
    );
    m_query.bindValue(":id", id);

    if (!m_query.exec())
        error();

    QPixmap cover;
    if (m_query.first())
    {
        const QByteArray bytes = m_query.value(0).toByteArray();
        cover.loadFromData(bytes);
    }
    return cover;
}

QString Cache::dbName()
{
    return SQL_CONNECTION + QString::number(reinterpret_cast<quint64>(QThread::currentThread()), 16);
}

QSqlDatabase Cache::db()
{
    QSqlDatabase db = QSqlDatabase::database(dbName(), false);
    db.setDatabaseName(SQL_PATH);
    db.open();

    return db;
}

QByteArray Cache::coverToBytes(const QPixmap &cover)
{
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    cover.save(&buffer, "PNG");

    return bytes;
}

void Cache::createCovers()
{
    m_query.prepare(
        "CREATE TABLE IF NOT EXISTS covers("
        " id INTEGER PRIMARY KEY,"
        " size INTEGER,"
        " cover BLOB"
        ")"
    );

    if (!m_query.exec())
        error();
}

void Cache::createAudios()
{
    m_query.prepare(
        "CREATE TABLE IF NOT EXISTS audios("
        " path TEXT PRIMARY KEY,"
        " title TEXT,"
        " artist TEXT,"
        " album TEXT,"
        " genre TEXT,"
        " year INTEGER,"
        " track INTEGER,"
        " duration INTEGER,"
        " coverid INTEGER,"
        " modified INTEGER"
        ")"
    );

    if (!m_query.exec())
        error();
}

bool Cache::defaultCoverExists()
{
    m_query.prepare(
        "SELECT 1 FROM covers "
        "WHERE id = 1"
    );

    if (!m_query.exec())
        error();

    return m_query.first();
}

void Cache::insertDefaultCover()
{
    if (defaultCoverExists())
        return;

    const QPixmap cover = Cover::scale(QPixmap(IMG_DEFAULT_COVER), Cover::defaultSize());
    const QByteArray bytes = coverToBytes(cover);

    m_query.prepare(
        "INSERT INTO covers VALUES ("
        " :id,"
        " :size,"
        " :cover"
        ")"
    );
    m_query.bindValue(":id", 1);
    m_query.bindValue(":size", bytes.size());
    m_query.bindValue(":cover", bytes);

    if (!m_query.exec())
        error();
}

int Cache::insertByteCover(const QByteArray &bytes)
{
    static QMutex mutex;
    const QMutexLocker locker(&mutex);
    const int id = lastCoverId() + 1;

    m_query.prepare(
        "INSERT INTO covers VALUES ("
        " :id,"
        " :size,"
        " :cover"
        ")"
    );
    m_query.bindValue(":id", id);
    m_query.bindValue(":size", bytes.size());
    m_query.bindValue(":cover", bytes);

    if (!m_query.exec())
    {
        error();
        return 0;
    }
    return id;
}

void Cache::updateByteCover(int id, const QByteArray &bytes)
{
    m_query.prepare(
        "UPDATE covers SET"
        " cover = :cover "
        "WHERE id = :id"
    );
    m_query.bindValue(":cover", bytes);
    m_query.bindValue(":id", id);

    if (!m_query.exec())
        error();
}

int Cache::coverId(const QByteArray &bytes)
{
    int id = coverIdBySize(bytes.size());
    if (id == 0)
        id = coverIdByBlob(bytes);

    return id;
}

int Cache::lastCoverId()
{
    m_query.prepare("SELECT max(id) FROM covers");

    if (!m_query.exec())
        error();

    int id = 1;
    if (m_query.first())
        id = m_query.value(0).toInt();

    return id;
}

int Cache::coverIdBySize(int size)
{
    m_query.prepare(
        "SELECT id FROM covers "
        "WHERE size = :size"
    );
    m_query.bindValue(":size", size);

    if (!m_query.exec())
        error();

    int id = 0;
    if (m_query.first())
        id = m_query.value(0).toInt();
    if (m_query.next())
        id = 0;

    return id;
}

int Cache::coverIdByBlob(const QByteArray &bytes)
{
    m_query.prepare(
        "SELECT id FROM covers "
        "WHERE cover = :cover"
    );
    m_query.bindValue(":cover", bytes);

    if (!m_query.exec())
        error();

    int id = 0;
    if (m_query.first())
        id = m_query.value(0).toInt();

    return id;
}

void Cache::error()
{
    const QSqlError error = m_query.lastError();
    if (error.type() == QSqlError::NoError)
        return;

    LOG("Querying \"%1\" failed with errors \"%2\" and \"%3\"", lastQuery(), error.databaseText(), error.driverText());
}

QString Cache::lastQuery()
{
    QString query = m_query.lastQuery();
    QMapIterator<QString, QVariant> iter(m_query.boundValues());
    while (iter.hasNext())
    {
        iter.next();
        query.replace(iter.key(), iter.value().toString());
    }
    return query;
}
