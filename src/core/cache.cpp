#include "cache.hpp"

Cache::Cache()
{

}

Cache::~Cache()
{

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

    if (m_db.open())
    {
        QSqlQuery query(m_db);
        query.exec(
            "CREATE TABLE IF NOT EXISTS covers("
            "  id INTEGER PRIMARY KEY,"
            "  len INTEGER,"
            "  cover BLOB"
            ")"
        );
        query.exec(
            "CREATE TABLE IF NOT EXISTS audios("
            "  path TEXT PRIMARY KEY,"
            "  coverid INTEGER,"
            "  FOREIGN KEY (coverid) REFERENCES covers(id)"
            ")"
        );
        return true;
    }
    return false;
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

    QSqlQuery query(m_db);
    query.prepare("INSERT INTO audios VALUES (:PATH, :COVERID)");
    query.bindValue(":PATH", audio->path());
    query.bindValue(":COVERID", id);

    return query.exec();
}

bool Cache::exists(Audio *audio)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT 1 FROM audios WHERE path = :PATH LIMIT 1");
    query.bindValue(":PATH", audio->path());
    query.exec();

    return query.first();
}

QPixmap Cache::cover(const QString &path, int size)
{
    QSqlQuery query = QSqlQuery(m_db);
    query.prepare(
        "SELECT covers.cover FROM audios "
        "JOIN covers ON audios.coverid = covers.id "
        "WHERE path = :PATH LIMIT 1"
    );
    query.bindValue(":PATH", path);
    query.exec();

    if (query.first())
    {
        QByteArray bytes = query.value(0).toByteArray();
        QPixmap image;
        image.loadFromData(bytes);
        return scale(image, size);
    }
    return scale(QPixmap(IMG_DEFAULT_COVER), size);
}

int Cache::lastCoverId()
{
    QSqlQuery query(m_db);
    query.exec("SELECT max(id) FROM covers LIMIT 1");

    if (query.first())
        return query.value(0).toInt();

    return 0;
}

QByteArray Cache::coverToBytes(const QPixmap &cover)
{
    QByteArray bytes;

    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    cover.save(&buffer, "PNG");

    return bytes;
}

int Cache::coverId(const QByteArray &bytes)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT id FROM covers WHERE len = :LEN");
    query.bindValue(":LEN", bytes.length());
    query.exec();

    if (query.first())
    {
        int id = query.value(0).toInt();

        if (!query.next())
        {
            return id;
        }
        else
        {
            query.prepare("SELECT id FROM covers WHERE cover = :COVER LIMIT 1");
            query.bindValue(":COVER", bytes);
            query.exec();

            if (query.first())
                return query.value(0).toInt();
        }
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
    query.exec();

    return id;
}

QPixmap Cache::scale(const QPixmap &pixmap, int size)
{
    return pixmap.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}
