#include "cache.hpp"

Cache::Cache()
{

}

bool Cache::connect()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(SQL_DB_NAME);

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

bool Cache::insert(QString file, QPixmap cover)
{
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    cover.save(&buffer, "PNG");

    m_query.prepare(SQL_INSERT);
    m_query.bindValue(":FILE", QVariant(file));
    m_query.bindValue(":COVER", QVariant(bytes));

    return m_query.exec();
}

bool Cache::exists(QString file)
{
    m_query.prepare(SQL_RETRIEVE);
    m_query.bindValue(":FILE", QVariant(file));

    return m_query.exec() && m_query.first();
}

QPixmap Cache::cover(QString file, int size)
{
    m_query.prepare(SQL_RETRIEVE);
    m_query.bindValue(":FILE", QVariant(file));

    if (m_query.exec())
    {
        if (m_query.first())
        {
            QByteArray bytes = m_query.value(0).toByteArray();
            QPixmap cover;
            cover.loadFromData(bytes);
            return cover.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }
    }
    return QPixmap();
}
