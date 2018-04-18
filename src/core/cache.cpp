#include "cache.hpp"

Cache::Cache()
{

}

Cache::~Cache()
{
    m_db.close();
}

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
        Logger::log(QString("Failed opening database"));
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

void Cache::close()
{
    m_db.close();
}

bool Cache::insert(Audio *audio)
{
    QByteArray bytes = coverToBytes(audio->cover(200));

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
        Logger::log(QString("Failed loading cover of '%1'").arg(path));
    }
    return scale(image, size);
}

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

void Cache::handleError(const QSqlQuery &query)
{
    QSqlError error = query.lastError();
    if (error.isValid())
    {
        QString message = "Failed querying '%1' with error '%2'";
        Logger::log(message.arg(lastQuery(query)).arg(error.databaseText()));
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

QPixmap Cache::scale(const QPixmap &pixmap, int size)
{
    return pixmap.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}
