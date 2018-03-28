#include "cache.hpp"

Cache::Cache()
{

}

Cache::~Cache()
{

}

bool Cache::connect()
{
    if (QSqlDatabase::contains(SQL_DB_NAME))
    {
        m_db = QSqlDatabase::database(SQL_DB_NAME, false);
    }
    else
    {
        m_db = QSqlDatabase::addDatabase("QSQLITE", SQL_DB_NAME);
        m_db.setDatabaseName(SQL_DB_NAME);
    }

    if (m_db.open())
    {
        QSqlQuery query = QSqlQuery(m_db);
        query.exec(SQL_CREATE_TABLE);
        return true;
    }
    return false;
}

void Cache::close()
{
    m_db.close();
}

bool Cache::insert(const QString &artist, const QString &album, const QPixmap &cover)
{
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    cover.save(&buffer, "PNG");

    QSqlQuery query = QSqlQuery(m_db);
    query.prepare(SQL_INSERT);
    query.bindValue(":ARTIST", QVariant(artist));
    query.bindValue(":ALBUM", QVariant(album));
    query.bindValue(":COVER", QVariant(bytes));

    return query.exec();
}

bool Cache::exists(const QString &artist, const QString &album)
{
    QSqlQuery query = QSqlQuery(m_db);
    query.prepare(SQL_RETRIEVE);
    query.bindValue(":ARTIST", QVariant(artist));
    query.bindValue(":ALBUM", QVariant(album));

    return query.exec() && query.first();
}

QPixmap Cache::cover(const QString &artist, const QString &album, int size)
{
    QSqlQuery query = QSqlQuery(m_db);
    query.prepare(SQL_RETRIEVE);
    query.bindValue(":ARTIST", QVariant(artist));
    query.bindValue(":ALBUM", QVariant(album));

    if (query.exec())
    {
        if (query.first())
        {
            QByteArray bytes = query.value(0).toByteArray();
            QPixmap image;
            image.loadFromData(bytes);
            return scale(image, size);
        }
    }
    return scale(QPixmap(IMG_DEFAULT_COVER), size);
}

QPixmap Cache::scale(QPixmap image, int size)
{
    return image.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}
