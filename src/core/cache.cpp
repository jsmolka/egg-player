#include "cache.hpp"

Cache::Cache()
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
        m_query = QSqlQuery(m_db);
        m_query.exec(SQL_CREATE_TABLE);
        return true;
    }
    return false;
}

void Cache::close()
{
    m_db.close();
}

bool Cache::insert(QString artist, QString album, QPixmap cover)
{
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    cover.save(&buffer, "PNG");

    m_query.prepare(SQL_INSERT);
    m_query.bindValue(":ARTIST", QVariant(artist));
    m_query.bindValue(":ALBUM", QVariant(album));
    m_query.bindValue(":COVER", QVariant(bytes));

    return m_query.exec();
}

bool Cache::exists(QString artist, QString album)
{
    m_query.prepare(SQL_RETRIEVE);
    m_query.bindValue(":ARTIST", QVariant(artist));
    m_query.bindValue(":ALBUM", QVariant(album));

    return m_query.exec() && m_query.first();
}

QPixmap Cache::cover(QString artist, QString album, int size)
{
    m_query.prepare(SQL_RETRIEVE);
    m_query.bindValue(":ARTIST", QVariant(artist));
    m_query.bindValue(":ALBUM", QVariant(album));

    if (m_query.exec())
    {
        if (m_query.first())
        {
            QByteArray bytes = m_query.value(0).toByteArray();
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
