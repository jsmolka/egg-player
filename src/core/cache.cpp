#include "cache.hpp"

/*
 * Constructor.
 */
Cache::Cache()
{

}

/*
 * Destructor.
 */
Cache::~Cache()
{
    m_db.close();
}

/*
 * Connects to database. Either adds it
 * to sql database or opens it from there.
 *
 * :return: success
 */
bool Cache::connect()
{
    if (QSqlDatabase::contains(SQL_CONNECTION))
    {
        m_db = QSqlDatabase::database(SQL_CONNECTION, false);
    }
    else
    {
        m_db = QSqlDatabase::addDatabase("QSQLITE", SQL_CONNECTION);
        m_db.setDatabaseName(SQL_PATH);
    }

    if (!m_db.open())
    {
        Logger::log("Cache: Cannot open database");
        return false;
    }

    QString createCovers =
        "CREATE TABLE IF NOT EXISTS covers("
        " id INTEGER PRIMARY KEY,"
        " len INTEGER,"
        " cover BLOB"
        ")";

    QString createAudios =
        "CREATE TABLE IF NOT EXISTS audios("
        " path TEXT PRIMARY KEY,"
        " coverid INTEGER,"
        " FOREIGN KEY (coverid) REFERENCES covers(id)"
        ")";

    QSqlQuery query(m_db);
    if (!query.exec(createCovers))
    {
        handleError(query);
        return false;
    }
    if (!query.exec(createAudios))
    {
        handleError((query));
        return false;
    }
    return true;
}

/*
 * Closes database connection.
 */
void Cache::close()
{
    m_db.close();
}

/*
 * Inserts audio into cache. It adds the cover
 * into the covers table and the path with a
 * cover id into the audios table. No tags are
 * stored inside the cache because taglib is
 * fast enough to reload tags at every startup.
 *
 * :param audio: pointer to audio
 * :param size: size of inserted cover, default 200
 * :return: success
 */
bool Cache::insert(Audio *audio, int size)
{
    QByteArray bytes = coverToBytes(audio->cover(size));

    int id = coverId(bytes);
    if (id == -1)
        id = insertCover(bytes);
    if (id == -1)
        // Unable to insert cover
        return false;

    QSqlQuery query(m_db);
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
 * Checks if audio exists inside
 * audios table.
 *
 * :param audio: pointer to audio
 * :return: exists
 */
bool Cache::exists(Audio *audio)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT 1 FROM audios WHERE path = :PATH");
    query.bindValue(":PATH", audio->path());
    if (!query.exec())
    {
        handleError(query);
        // Assume audio exists to prevent duplicate primary key
        return true;
    }
    return query.first();
}

/*
 * Retrieves cover from database.
 *
 * :param path: path of audio
 * :param size: size of cover
 * :return: db cover or default cover
 */
QPixmap Cache::cover(const QString &path, int size)
{
    QSqlQuery query = QSqlQuery(m_db);
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
        image = QPixmap(IMG_DEFAULT_COVER);
        Logger::log("Cache: Cannot load cover '%1'", path);
    }
    return scale(image, size);
}

/*
 * Gets last cover id by getting
 * the max id values.
 *
 * :return: last cover id
 */
int Cache::lastCoverId()
{
    QSqlQuery query(m_db);
    query.prepare("SELECT max(id) FROM covers");
    if (!query.exec())
        handleError(query);
    if (query.first())
        return query.value(0).toInt();
    return 0;
}

/*
 * Finds cover id of cover in form of
 * byte array. First it tries to query by
 * byte array length instead of blob comparison
 * for performance purposes. If there are multiple
 * results it uses blob comparison to query for
 * the exact cover.
 *
 * :param bytes: cover in byte array form
 * :return: cover id or -1
 */
int Cache::coverId(const QByteArray &bytes)
{
    // Try to get cover by byte array length for better performance
    QSqlQuery query(m_db);
    query.prepare("SELECT id FROM covers WHERE len = :LEN");
    query.bindValue(":LEN", bytes.length());
    if (!query.exec())
        handleError(query);
    if (query.first())
    {
        int id = query.value(0).toInt();
        if (!query.next())
            // Return if id if there is only one result
            return id;

        // Get cover by blob comparison if there are multiple results
        query.prepare("SELECT id FROM covers WHERE cover = :COVER");
        query.bindValue(":COVER", bytes);
        if (!query.exec())
            handleError(query);
        if (query.first())
            return query.value(0).toInt();
    }
    return -1;
}

/*
 * Inserts cover into database. Assumes
 * that the cover does not exist already.
 *
 * :param bytes: cover in byte array form
 * :return: cover id or -1
 */
int Cache::insertCover(const QByteArray &bytes)
{
    int id = lastCoverId() + 1;

    QSqlQuery query(m_db);
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
 * Handles query errors by logging the
 * used query with binded values.
 *
 * :param query: failed query
 */
void Cache::handleError(const QSqlQuery &query)
{
    QSqlError error = query.lastError();
    if (error.isValid())
        Logger::log(
            "Cache: Query '%1' failed with error '%2'",
            lastQuery(query),
            error.databaseText()
        );
}

/*
 * Gets the last query in string form by
 * binding all used values to show them
 * properly.
 *
 * :param query: used query
 * :return: string with bound values
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
 * :param cover: cover to convert
 * :return: converted cover
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
 * Scales pixmap.
 *
 * :param pixmap: pixmap to scale
 * :param size: size to scale to
 * :return: scales pixmap
 */
QPixmap Cache::scale(const QPixmap &pixmap, int size)
{
    return pixmap.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}
