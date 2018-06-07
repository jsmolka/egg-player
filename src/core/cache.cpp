#include "cache.hpp"

Cache::Cache()
{    
    if (!QSqlDatabase::contains(dbName()))
    {
        QSqlDatabase::addDatabase("QSQLITE", dbName());

        m_db = db();

        createCovers();
        createAudios();
    }
    else
    {
        m_db = db();
    }
}

Cache::~Cache()
{

}

Audio * Cache::load(const QString &path)
{
    Audio *audio = nullptr;

    QSqlQuery query(m_db);
    query.prepare(
        "SELECT * FROM audios "
        "WHERE path = :path"
    );
    query.bindValue(":path", path);

    if (!query.exec())
        handleError(query);

    if (query.first())
    {
        audio = new Audio(
            query.value(0).toString(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toString(),
            query.value(5).toInt(),
            query.value(6).toInt(),
            query.value(7).toInt(),
            query.value(8).toInt()
        );
    }
    return audio;
}

bool Cache::insertAudio(Audio *audio)
{
    QSqlQuery query(m_db);
    query.prepare(
        "INSERT INTO audios VALUES ("
        " :path,"
        " :title,"
        " :artist,"
        " :album,"
        " :genre,"
        " :year,"
        " :track,"
        " :length,"
        " :coverid"
        ")"
    );
    query.bindValue(":path", audio->path());
    query.bindValue(":title", audio->title());
    query.bindValue(":artist", audio->artist());
    query.bindValue(":album", audio->album());
    query.bindValue(":genre", audio->genre());
    query.bindValue(":year", audio->year());
    query.bindValue(":track", audio->track());
    query.bindValue(":length", audio->length(false));
    query.bindValue(":coverid", audio->coverId());

    if (!query.exec())
    {
        handleError(query);
        return false;
    }
    return true;
}

bool Cache::insertCover(Audio *audio, int size)
{
    int id = getOrInsertCover(audio->cover(size));
    if (id == -1)
        return false;

    audio->setCoverId(id);

    QSqlQuery query(m_db);
    query.prepare(
        "UPDATE audios "
        "SET coverid = :coverid "
        "WHERE path = :path"
    );
    query.bindValue(":path", audio->path());
    query.bindValue(":coverid", id);

    if (!query.exec())
    {
        handleError(query);
        return false;
    }
    return true;
}

bool Cache::contains(Audio *audio)
{
    if (audio->coverId() != -1)
        return true;

    QSqlQuery query(m_db);
    query.prepare(
        "SELECT coverid FROM audios "
        "WHERE path = :path"
    );
    query.bindValue(":path", audio->path());

    if (!query.exec())
    {
        handleError(query);
        return true;
    }

    if (!query.first())
        return false;

    int id = query.value(0).toInt();
    if (id == -1)
        return false;

    audio->setCoverId(id);

    return true;
}

QPixmap Cache::cover(Audio *audio, int size)
{
    if (_covers.contains(audio->coverId()))
        return _covers.value(audio->coverId());

    QSqlQuery query(m_db);
    query.prepare(
        "SELECT covers.cover FROM audios "
        "JOIN covers ON audios.coverid = covers.id "
        "WHERE path = :path"
    );
    query.bindValue(":path", audio->path());

    if (!query.exec())
        handleError(query);

    QPixmap pixmap;
    if (query.first())
    {
        QByteArray bytes = query.value(0).toByteArray();
        pixmap.loadFromData(bytes);
    }

    if (pixmap.isNull())
    {
        pixmap = Util::cover();
        Logger::log("Cache: Cannot load cover %1", {audio->path()});
    }

    pixmap = Util::resize(pixmap, size);
    _covers.insert(audio->coverId(), pixmap);

    return pixmap;
}

QString Cache::dbName()
{
    return SQL_CONNECTION + QString::number(reinterpret_cast<quint64>(QThread::currentThread()), 16);
}

QSqlDatabase Cache::db()
{
    QSqlDatabase db = QSqlDatabase::database(dbName(), false);
    db.setDatabaseName(SQL_PATH);
    if (!db.isOpen())
        if (!db.open())
            Logger::log("Cache: Cannot open database");

    return db;
}

void Cache::createCovers()
{
    QString create =
        "CREATE TABLE IF NOT EXISTS covers("
        " id INTEGER PRIMARY KEY,"
        " len INTEGER,"
        " cover BLOB"
        ")";

    QSqlQuery query(m_db);
    if (!query.exec(create))
        handleError((query));
}

void Cache::createAudios()
{
    QString create =
        "CREATE TABLE IF NOT EXISTS audios("
        " path TEXT PRIMARY KEY,"
        " title TEXT,"
        " artist TEXT,"
        " album TEXT,"
        " genre TEXT,"
        " year INTEGER,"
        " track INTEGER,"
        " length INTEGER,"
        " coverid INTEGER"
        ")";

    QSqlQuery query(m_db);
    if (!query.exec(create))
        handleError(query);
}

int Cache::getOrInsertCover(const QPixmap &cover)
{
    QByteArray bytes = coverToBytes(cover);

    int id = coverId(bytes);
    if (id == -1)
        id = insertByteCover(bytes);

    return id;
}

int Cache::insertByteCover(const QByteArray &bytes)
{
    int id = lastCoverId() + 1;

    QSqlQuery query(m_db);
    query.prepare(
        "INSERT INTO covers VALUES ("
        " :id,"
        " :len,"
        " :cover"
        ")"
    );
    query.bindValue(":id", id);
    query.bindValue(":len", bytes.length());
    query.bindValue(":cover", bytes);

    if (!query.exec())
    {
        handleError(query);
        return -1;
    }
    return id;
}

int Cache::coverId(const QByteArray &bytes)
{
    int id = queryCoverIdByLength(bytes.length());

    if (id == -1)
        id = queryCoverIdByBlob(bytes);

    return id;
}

int Cache::lastCoverId()
{
    QSqlQuery query(m_db);

    if (!query.exec("SELECT max(id) FROM covers"))
        handleError(query);

    if (query.first())
        return query.value(0).toInt();

    return -1;
}

int Cache::queryCoverIdByLength(int length)
{
    int id = -1;

    QSqlQuery query(m_db);
    query.prepare(
        "SELECT id FROM covers "
        "WHERE len = :len"
    );
    query.bindValue(":len", length);

    if (!query.exec())
        handleError(query);

    if (query.first())
        id = query.value(0).toInt();

    if (query.next())
        id = -1;

    return id;
}

int Cache::queryCoverIdByBlob(const QByteArray &bytes)
{
    QSqlQuery query(m_db);
    query.prepare(
        "SELECT id FROM covers "
        "WHERE cover = :cover"
    );
    query.bindValue(":cover", bytes);

    if (!query.exec())
        handleError(query);

    if (query.first())
        return query.value(0).toInt();

    return -1;
}

void Cache::handleError(const QSqlQuery &query)
{
    QSqlError error = query.lastError();
    if (error.type() != QSqlError::NoError)
    {
        Logger::log(
            "Cache: Querying \"%1\" failed with error \"%2\"",
            {
                lastQuery(query),
                error.databaseText()
            }
        );
    }
}

QString Cache::lastQuery(const QSqlQuery &query)
{
    QString string = query.lastQuery();
    QMapIterator<QString, QVariant> iter(query.boundValues());

    while (iter.hasNext())
    {
        iter.next();
        string.replace(iter.key(), iter.value().toString());
    }
    return string;
}

QByteArray Cache::coverToBytes(const QPixmap &cover)
{
    QByteArray bytes;

    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    cover.save(&buffer, "PNG");

    return bytes;
}

QHash<int, QPixmap> Cache::_covers;
