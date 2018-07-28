#include "cache.hpp"

Cache::Cache()
{    
    if (!QSqlDatabase::contains(dbName()))
        QSqlDatabase::addDatabase("QSQLITE", dbName());

    m_db = db();
    m_query = QSqlQuery(m_db);
    m_query.setForwardOnly(true);

    if (!_created)
        createTables();
}

Cache::~Cache()
{

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

Audio * Cache::loadAudio(const QString &path)
{
    Audio *audio = nullptr;

    m_query.prepare(
        "SELECT * FROM audios "
        "WHERE path = :path"
    );
    m_query.bindValue(":path", path);

    if (!m_query.exec())
        handleError();

    if (m_query.first())
    {
        audio = new Audio(
            m_query.value(0).toString(),
            m_query.value(1).toString(),
            m_query.value(2).toString(),
            m_query.value(3).toString(),
            m_query.value(4).toString(),
            m_query.value(5).toInt(),
            m_query.value(6).toInt(),
            m_query.value(7).toInt(),
            m_query.value(8).toInt()
        );
    }
    return audio;
}

void Cache::insertAudio(Audio *audio)
{
    m_query.prepare(
        "INSERT INTO audios VALUES ("
        "  :path,"
        "  :title,"
        "  :artist,"
        "  :album,"
        "  :genre,"
        "  :year,"
        "  :track,"
        "  :duration,"
        "  :coverid"
        ")"
    );
    m_query.bindValue(":path", audio->path());
    m_query.bindValue(":title", audio->title());
    m_query.bindValue(":artist", audio->artist());
    m_query.bindValue(":album", audio->album());
    m_query.bindValue(":genre", audio->genre());
    m_query.bindValue(":year", audio->year());
    m_query.bindValue(":track", audio->track());
    m_query.bindValue(":duration", audio->duration().secs());
    m_query.bindValue(":coverid", audio->cover().id());

    if (!m_query.exec())
        handleError();

    audio->setCached(true);
}

void Cache::updateAudio(Audio *audio)
{
    m_query.prepare(
        "UPDATE audios SET"
        "  path = :path,"
        "  title = :title,"
        "  artist = :artist,"
        "  album = :album,"
        "  genre = :genre,"
        "  year = :year,"
        "  track = :track,"
        "  duration = :duration,"
        "  coverid = :coverid"
        "WHERE path = :path"
    );
    m_query.bindValue(":path", audio->path());
    m_query.bindValue(":title", audio->title());
    m_query.bindValue(":artist", audio->artist());
    m_query.bindValue(":album", audio->album());
    m_query.bindValue(":genre", audio->genre());
    m_query.bindValue(":year", audio->year());
    m_query.bindValue(":track", audio->track());
    m_query.bindValue(":duration", audio->duration().secs());
    m_query.bindValue(":coverid", audio->cover().id());

    if (!m_query.exec())
        handleError();
}

int Cache::insertCover(const QPixmap &cover)
{
    QByteArray bytes = coverToBytes(cover);

    int id = coverId(bytes);
    if (id == -1)
        id = insertByteCover(bytes);

    return id;
}

void Cache::setAudioCoverId(Audio *audio, int id)
{
    m_query.prepare(
        "UPDATE audios SET"
        "  coverid = :coverid "
        "WHERE path = :path"
    );
    m_query.bindValue(":path", audio->path());
    m_query.bindValue(":coverid", id);

    if (!m_query.exec())
        handleError();
}

QPixmap Cache::coverById(int id)
{
    m_query.prepare(
        "SELECT cover FROM covers "
        "WHERE id = :id"
    );
    m_query.bindValue(":id", id);

    if (!m_query.exec())
        handleError();

    QPixmap cover;
    if (m_query.first())
    {
        QByteArray bytes = m_query.value(0).toByteArray();
        cover.loadFromData(bytes);
    }
    return cover;
}

QPixmap Cache::coverByAudio(Audio *audio)
{
    m_query.prepare(
        "SELECT covers.cover FROM audios "
        "JOIN covers ON audios.coverid = covers.id "
        "WHERE path = :path"
    );
    m_query.bindValue(":path", audio->path());

    if (!m_query.exec())
        handleError();

    QPixmap cover;
    if (m_query.first())
    {
        QByteArray bytes = m_query.value(0).toByteArray();
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

void Cache::createCovers()
{
    QString create =
        "CREATE TABLE IF NOT EXISTS covers("
        "  id INTEGER PRIMARY KEY,"
        "  size INTEGER,"
        "  cover BLOB"
        ")";

    if (m_query.exec(create))
        handleError();
}

void Cache::createAudios()
{
    QString create =
        "CREATE TABLE IF NOT EXISTS audios("
        "  path TEXT PRIMARY KEY,"
        "  title TEXT,"
        "  artist TEXT,"
        "  album TEXT,"
        "  genre TEXT,"
        "  year INTEGER,"
        "  track INTEGER,"
        "  length INTEGER,"
        "  coverid INTEGER"
        ")";

    if (!m_query.exec(create))
        handleError();
}

void Cache::createTables()
{
    if (_created)
        return;

    createCovers();
    createAudios();
    _created = true;
}

int Cache::insertByteCover(const QByteArray &bytes)
{
    int id = lastCoverId() + 1;

    m_query.prepare(
        "INSERT INTO covers VALUES ("
        "  :id,"
        "  :size,"
        "  :cover"
        ")"
    );
    m_query.bindValue(":id", id);
    m_query.bindValue(":size", bytes.size());
    m_query.bindValue(":cover", bytes);

    if (!m_query.exec())
    {
        handleError();
        return -1;
    }
    return id;
}

int Cache::coverId(const QByteArray &bytes)
{
    int id = queryCoverIdBySize(bytes.size());

    if (id == -1)
        id = queryCoverIdByBlob(bytes);

    return id;
}

int Cache::lastCoverId()
{
    if (!m_query.exec("SELECT max(id) FROM covers"))
        handleError();

    if (m_query.first())
        return m_query.value(0).toInt();

    return -1;
}

int Cache::queryCoverIdBySize(int size)
{
    int id = -1;

    m_query.prepare(
        "SELECT id FROM covers "
        "WHERE size = :size"
    );
    m_query.bindValue(":size", size);

    if (!m_query.exec())
        handleError();

    if (m_query.first())
        id = m_query.value(0).toInt();

    if (m_query.next())
        id = -1;

    return id;
}

int Cache::queryCoverIdByBlob(const QByteArray &bytes)
{
    m_query.prepare(
        "SELECT id FROM covers "
        "WHERE cover = :cover"
    );
    m_query.bindValue(":cover", bytes);

    if (!m_query.exec())
        handleError();

    if (m_query.first())
        return m_query.value(0).toInt();

    return -1;
}

void Cache::handleError()
{
    QSqlError error = m_query.lastError();
    if (error.type() != QSqlError::NoError)
        log("Cache: Querying \"%1\" failed with error \"%2\"", {lastQuery(), error.databaseText()});
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

QByteArray Cache::coverToBytes(const QPixmap &cover)
{
    QByteArray bytes;

    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    cover.save(&buffer, "PNG");

    return bytes;
}

bool Cache::_created = false;
