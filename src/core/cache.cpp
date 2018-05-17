#include "cache.hpp"

/*
 * Constructor. If the QSqlDatabase does not contain the database it gets added
 * and the tables get created.
 */
Cache::Cache()
{
    if (QSqlDatabase::contains(SQL_CONNECTION))
        return;

    QSqlDatabase::addDatabase("QSQLITE", SQL_CONNECTION);

    createCovers();
    createAudios();
}

/*
 * Destructor.
 */
Cache::~Cache()
{

}

/*
 * Inserts audio into cache. It adds the cover into the covers table and the
 * path with a cover id into the audios table. No tags are stored inside the
 * cache because TagLib is fast enough to reload tags at every startup.
 *
 * :param audio: audio
 * :param size: cover size, default 200
 * :return: success
 */
bool Cache::insert(Audio *audio, int size)
{
    int id = getOrInsertCover(audio->cover(size));
    if (id == -1)
        return false;

    QSqlQuery query(db());
    query.prepare("INSERT INTO audios VALUES (:PATH, :COVERID)");
    query.bindValue(":PATH", audio->path());
    query.bindValue(":COVERID", id);

    if (!query.exec())
    {
        handleError(query);
        return false;
    }
    return true;
}

/*
 * Checks if database contains audio.
 *
 * :param audio: audio
 * :return: contains
 */
bool Cache::contains(Audio *audio)
{
    QSqlQuery query(db());
    query.prepare("SELECT 1 FROM audios WHERE path = :PATH");
    query.bindValue(":PATH", audio->path());

    if (!query.exec())
    {
        handleError(query);
        return true;
    }
    return query.first();
}

/*
 * Retrieves cover from database.
 *
 * :param path: audio path
 * :param size: cover size, default 200
 * :return: cover
 */
QPixmap Cache::cover(const QString &path, int size)
{
    QSqlQuery query = QSqlQuery(db());
    query.prepare(
        "SELECT covers.cover FROM audios "
        "JOIN covers ON audios.coverid = covers.id "
        "WHERE path = :PATH"
    );
    query.bindValue(":PATH", path);

    if (!query.exec())
        handleError(query);

    QPixmap image;
    if (query.first())
    {
        QByteArray bytes = query.value(0).toByteArray();
        image.loadFromData(bytes);
    }

    if (image.isNull())
    {
        image = Utils::defaultCover();
        Logger::log("Cache: Cannot load cover %1", {path});
    }
    return Utils::resize(image, size);
}

/*
 * Returns the current database.
 *
 * :return: database
 */
QSqlDatabase Cache::db()
{
    QSqlDatabase db = QSqlDatabase::database(SQL_CONNECTION, false);
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
        " coverid INTEGER,"
        " FOREIGN KEY (coverid) REFERENCES covers(id)"
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
    query.prepare("INSERT INTO covers VALUES (:ID, :LEN, :COVER)");
    query.bindValue(":ID", id);
    query.bindValue(":LEN", bytes.length());
    query.bindValue(":COVER", bytes);

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
    query.prepare("SELECT max(id) FROM covers");

    if (!query.exec())
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
    query.prepare("SELECT id FROM covers WHERE len = :LEN");
    query.bindValue(":LEN", length);

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
    query.prepare("SELECT id FROM covers WHERE cover = :COVER");
    query.bindValue(":COVER", bytes);

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

    while(iter.hasNext())
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
