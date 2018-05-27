#include "cache.hpp"

/*
 * Constructor. If the QSqlDatabase does not contain the database it gets added
 * and the tables get created if they do not exist already.
 */
Cache::Cache()
{    
    if (!QSqlDatabase::contains(dbName()))
    {
        QSqlDatabase::addDatabase("QSQLITE", dbName());

        createCovers();
        createAudios();
    }
}

/*
 * Destructor.
 */
Cache::~Cache()
{

}

/*
 * Loads an audio file from the cache. If it does not exist a nullptr will be
 * returned instead.
 *
 * :param path: path
 * :return: audio, nullptr at failure
 */
Audio * Cache::load(const QString &path)
{
    Audio *audio = nullptr;

    QSqlQuery query(db());
    query.prepare("SELECT * FROM audios WHERE path = :path");
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

/*
 * Inserts audio tags into the cache.
 *
 * :param audio: audio
 * :return: success
 */
bool Cache::insertAudio(Audio *audio)
{
    QSqlQuery query(db());
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

/*
 * Inserts an audio cover into the cache. This assumes that the audio already
 * has an entry in the audio table.
 *
 * :param audio: audio
 * :param size: cover size, default 200
 * :return: success
 */
bool Cache::insertCover(Audio *audio, int size)
{
    int id = getOrInsertCover(audio->cover(size));
    if (id == -1)
        return false;

    audio->setCoverId(id);

    QSqlQuery query(db());
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

/*
 * Checks if database contains audio. Also sets the cover id for later use. If
 * an audio object has a valid cover id it definitely exists already because it
 * only gets set inside the cache.
 *
 * :param audio: audio
 * :return: contains
 */
bool Cache::contains(Audio *audio)
{
    if (audio->coverId() != -1)
        return true;

    QSqlQuery query(db());
    query.prepare("SELECT coverid FROM audios WHERE path = :path");
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

/*
 * Retrieves cover from database. If the cover has already been loaded
 * previously, a cached version will be used.
 *
 * :param audio: audio
 * :param size: cover size, default 200
 * :return: cover
 */
QPixmap Cache::cover(Audio *audio, int size)
{
    if (_covers.contains(audio->coverId()))
        return _covers.value(audio->coverId());

    QSqlQuery query(db());
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

/*
 * Gets the database name for the current thread. This is because connections
 * must be unique for every thread as stated in the documentation:
 *
 * "A connection can only be used from within the thread that created it. Moving
 * connections between threads or creating queries from a different thread is
 * not supported."
 *
 * :return: database name
 */
QString Cache::dbName()
{
    return SQL_CONNECTION + QString::number(reinterpret_cast<quint64>(QThread::currentThread()), 16);
}

/*
 * Returns the current database.
 *
 * :return: database
 */
QSqlDatabase Cache::db()
{
    QSqlDatabase db = QSqlDatabase::database(dbName(), false);
    db.setDatabaseName(SQL_PATH);
    if (!db.isOpen())
        if (!db.open())
            Logger::log("Cache: Cannot open database");

    return db;
}

/*
 * Creates the covers table if it does not exist already.
 */
void Cache::createCovers()
{
    QString createCovers =
        "CREATE TABLE IF NOT EXISTS covers("
        " id INTEGER PRIMARY KEY,"
        " len INTEGER,"
        " cover BLOB"
        ")";

    QSqlQuery query(db());
    if (!query.exec(createCovers))
        handleError((query));
}

/*
 * Creates the audios table if it does not exist already.
 */
void Cache::createAudios()
{
    QString createAudios =
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

    QSqlQuery query(db());
    if (!query.exec(createAudios))
        handleError(query);
}

/*
 * Either gets the cover id or inserts it into the covers tables and returns its
 * id.
 *
 * :param cover: cover
 * :return: id, -1 at failure
 */
int Cache::getOrInsertCover(const QPixmap &cover)
{
    QByteArray bytes = coverToBytes(cover);

    int id = coverId(bytes);
    if (id == -1)
        id = insertCover(bytes);

    return id;
}

/*
 * Inserts cover into database. Assumes that the cover does not exist already.
 *
 * :param bytes: byte array cover
 * :return: id, -1 at failure
 */
int Cache::insertCover(const QByteArray &bytes)
{
    int id = lastCoverId() + 1;

    QSqlQuery query(db());
    query.prepare("INSERT INTO covers VALUES (:id, :len, :cover)");
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

/*
 * Returns cover id for byte array cover. For performance reasons it first tries
 * to query based on the byte array length and then by blob comparison.
 *
 * :param bytes: byte array cover
 * :return: id, -1 at failure
 */
int Cache::coverId(const QByteArray &bytes)
{
    int id = queryCoverIdByLength(bytes.length());

    if (id == -1)
        id = queryCoverIdByBlob(bytes);

    return id;
}

/*
 * Returns last cover id.
 *
 * :return: id, -1 if table is empty
 */
int Cache::lastCoverId()
{
    QSqlQuery query(db());

    if (!query.exec("SELECT max(id) FROM covers"))
        handleError(query);

    if (query.first())
        return query.value(0).toInt();

    return -1;
}

/*
 * Tries to query the current cover by length comparison. If there are multiple
 * results this function is not able to query the correct cover.
 *
 * :param length: length
 * :return: id, -1 at failure
 */
int Cache::queryCoverIdByLength(int length)
{
    int id = -1;

    QSqlQuery query(db());
    query.prepare("SELECT id FROM covers WHERE len = :len");
    query.bindValue(":len", length);

    if (!query.exec())
        handleError(query);

    if (query.first())
        id = query.value(0).toInt();

    if (query.next())
        id = -1;

    return id;
}

/*
 * Tries to query the current cover by blob comparison.
 *
 * :param bytes: byte array cover
 * :return: id
 */
int Cache::queryCoverIdByBlob(const QByteArray &bytes)
{
    QSqlQuery query(db());
    query.prepare("SELECT id FROM covers WHERE cover = :cover");
    query.bindValue(":cover", bytes);

    if (!query.exec())
        handleError(query);

    if (query.first())
        return query.value(0).toInt();

    return -1;
}

/*
 * Handles query errors by logging the used query with bound values.
 *
 * :param query: query
 */
void Cache::handleError(const QSqlQuery &query)
{
    QSqlError error = query.lastError();
    if (error.isValid())
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

/*
 * Gets the last query in string form by binding all used values to show them
 * properly.
 *
 * :param query: query
 * :return: query string
 */
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

/*
 * Converts cover to bytes.
 *
 * :param cover: cover
 * :return: byte array cover
 */
QByteArray Cache::coverToBytes(const QPixmap &cover)
{
    QByteArray bytes;

    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    cover.save(&buffer, "PNG");

    return bytes;
}

/*
 * The cache within the cache. Prevents loading covers multiple times and
 * thereby decreases loading times.
 */
QHash<int, QPixmap> Cache::_covers;
