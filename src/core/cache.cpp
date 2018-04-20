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
 * Connects to the database by either adding it to
 * the sql database or reopening it from there. It
 * also creates the tables if they do not exist already.
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
 * :param audio: audio pointer
 * :param size: cover size, default 200
 * :return: success
 */
bool Cache::insert(Audio *audio, int size)
{
    QByteArray bytes = coverToBytes(audio->cover(size));

    int id = coverId(bytes);
    if (id == -1)
        id = insertCover(bytes);
    if (id == -1)
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
 * :param audio: audio pointer
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
        return true;
    }
    return query.first();
}

/*
 * Retrieves cover from database. If the
 * cover cannot be found it returns the
 * default cover.
 *
 * :param path: audiopath
 * :param size: cover size
 * :return: db or default cover
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
 * Returns last cover id or -1 if the
 * covers table is empty.
 *
 * :return: id
 */
int Cache::lastCoverId()
{
    QSqlQuery query(m_db);
    query.prepare("SELECT max(id) FROM covers");
    if (!query.exec())
        handleError(query);
    if (query.first())
        return query.value(0).toInt();
    return -1;
}

/*
 * Returns cover id for cover in byte array form.
 * For performance reasons it first tries to query
 * based on the byte array length. If it only returns
 * one result it can be returned.
 * Otherwise there are mulitple cover with the same
 * length and the query uses blob comparison instead.
 * If the cover id cannot be retrieved it returns -1.
 *
 * :param bytes: cover byte array
 * :return: cover id or -1
 */
int Cache::coverId(const QByteArray &bytes)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT id FROM covers WHERE len = :LEN");
    query.bindValue(":LEN", bytes.length());
    if (!query.exec())
        handleError(query);
    if (query.first())
    {
        int id = query.value(0).toInt();
        if (!query.next())
            return id;

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
 * :param bytes: cover byte array
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
 * used query with bound values.
 *
 * :param query: query
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
 * :return: cover byte array
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
 * :param pixmap: pixmap
 * :param size: size
 * :return: scaled pixmap
 */
QPixmap Cache::scale(const QPixmap &pixmap, int size)
{
    return pixmap.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}
