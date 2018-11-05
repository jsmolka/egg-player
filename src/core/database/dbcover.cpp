#include "dbcover.hpp"

#include <QBuffer>
#include <QMutex>
#include <QMutexLocker>

db::Cover::Cover()
    : m_id(0)
    , m_size(0)
{

}

bool db::Cover::exists()
{
    query().prepare(
        "SELECT 1 FROM audios "
        "WHERE id = :id"
    );
    query().bindValue(":id", m_id);

    return query().exec() && query().first();
}

bool db::Cover::insert()
{
    return insert(coverToBytes(m_cover));
}

bool db::Cover::commit()
{
    return commit(coverToBytes(m_cover));
}

bool db::Cover::createTable()
{
    return query().exec(
        "CREATE TABLE IF NOT EXISTS covers ("
        "  id INTEGER PRIMARY KEY,"
        "  size INTEGER,"
        "  cover BLOB"
        ")"
    );
}

bool db::Cover::getById(int id)
{
    return getBy("id", id);
}

bool db::Cover::getBySize(int size)
{
    return getBy("size", size);
}

bool db::Cover::getByCover(const QPixmap &cover)
{
    return getBy("cover", coverToBytes(cover));
}

bool db::Cover::getOrInsertCover(const QPixmap &cover)
{
    const QByteArray bytes = coverToBytes(cover);
    const int id = coverId(bytes);
    if (id == 0)
    {
        static QMutex mutex;
        const QMutexLocker locker(&mutex);

        m_id = nextId();
        m_cover = cover;
        return insert(bytes);
    }
    return getById(id);
}

bool db::Cover::updateId(int id)
{
    query().prepare(
        "UPDATE covers SET"
        "  id = :newid "
        "WHERE id = :id"
    );
    query().bindValue(":id", m_id);
    query().bindValue(":newid", id);

    m_id = id;

    return query().exec();
}

bool db::Cover::updateSize(int size)
{
    m_size = size;

    return update("size", size);
}

bool db::Cover::updateCover(const QPixmap &cover)
{
    m_cover = cover;
    const QByteArray bytes = coverToBytes(cover);

    return update("cover", bytes);
}

bool db::Cover::getBy(const QString &column, const QVariant &value)
{
    query().prepare(
        "SELECT * FROM covers "
        "WHERE " + column + " = :value"
    );
    query().bindValue(":value", value);

    if (!query().exec())
        return false;

    if (!query().first())
        return false;

    loadFromRecord(query().record());

    return true;
}

bool db::Cover::update(const QString &column, const QVariant &value)
{
    query().prepare(
        "UPDATE covers SET"
        "  " + column + " = :value "
        "WHERE id = :file"
    );
    query().bindValue(":id", m_id);
    query().bindValue(":value", value);

    return query().exec();
}

QByteArray db::Cover::coverToBytes(const QPixmap &cover)
{
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QBuffer::WriteOnly);
    cover.save(&buffer, "PNG");

    return bytes;
}

bool db::Cover::insert(const QByteArray &bytes)
{
    m_size = bytes.size();

    query().prepare(
        "INSERT INTO covers VALUES ("
        "  :id,"
        "  :size,"
        "  :cover"
        ")"
    );
    query().bindValue(":id", m_id);
    query().bindValue(":size", m_size);
    query().bindValue(":cover", bytes);

    return query().exec();
}

bool db::Cover::commit(const QByteArray &bytes)
{
    m_size = bytes.size();

    query().prepare(
        "UPDATE covers SET"
        "  size = :size"
        "  cover = :cover "
        "WHERE id = :id"
    );
    query().bindValue(":id", m_id);
    query().bindValue(":size", m_size);
    query().bindValue(":cover", bytes);

    return query().exec();
}

int db::Cover::lastId()
{
    query().exec("SELECT max(id) FROM covers");

    int id = 1;
    if (query().first())
        id = query().value(0).toInt();

    return id;
}

int db::Cover::nextId()
{
    return lastId() + 1;
}

int db::Cover::coverId(const QByteArray &bytes)
{
    int id = coverIdBySize(bytes);
    if (id == 0)
        id = coverIdByBlob(bytes);

    return id;
}

int db::Cover::coverIdBySize(const QByteArray &bytes)
{
    query().prepare(
        "SELECT id FROM covers "
        "WHERE size = :size"
    );
    query().bindValue(":size", bytes.size());
    query().exec();

    int id = 0;
    if (query().first())
    {
        const QSqlRecord record = query().record();
        id = record.value("id").toInt();
    }
    if (query().next())
        id = 0;

    return id;
}

int db::Cover::coverIdByBlob(const QByteArray &bytes)
{
    query().prepare(
        "SELECT id FROM covers "
        "WHERE cover = :cover"
    );
    query().bindValue(":cover", bytes);
    query().exec();

    int id = 0;
    if (query().first())
    {
        const QSqlRecord record = query().record();
        id = record.value("id").toInt();
    }
    return id;
}

void db::Cover::loadFromRecord(const QSqlRecord &record)
{
    m_id = record.value("id").toInt();
    m_size = record.value("size").toInt();
    m_cover.loadFromData(record.value("cover").toByteArray());
}
