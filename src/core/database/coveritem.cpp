#include "coveritem.hpp"

#include <QBuffer>
#include <QMutex>
#include <QMutexLocker>

db::CoverItem::CoverItem()
    : m_id(0)
    , m_size(0)
{

}

bool db::CoverItem::exists()
{
    query().prepare(
        "SELECT 1 FROM audios "
        "WHERE id = :id"
    );
    query().bindValue(":id", m_id);

    return query().exec() && query().first();
}

bool db::CoverItem::insert()
{
    return insert(coverToBytes(m_cover));
}

bool db::CoverItem::commit()
{
    return commit(coverToBytes(m_cover));
}

bool db::CoverItem::createTable()
{
    return query().exec(
        "CREATE TABLE IF NOT EXISTS covers ("
        "  id INTEGER PRIMARY KEY,"
        "  size INTEGER,"
        "  cover BLOB"
        ")"
    );
}

bool db::CoverItem::getById(int id)
{
    return getBy("id", id);
}

bool db::CoverItem::getBySize(int size)
{
    return getBy("size", size);
}

bool db::CoverItem::getByCover(const QPixmap &cover)
{
    return getBy("cover", coverToBytes(cover));
}

bool db::CoverItem::getOrInsertCover(const QPixmap &cover)
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

bool db::CoverItem::updateId(int id)
{
    query().prepare(
        "UPDATE covers SET"
        "  id = :newid "
        "WHERE id = :id"
    );
    query().bindValue(":id", m_id);
    query().bindValue(":newid", id);

    if (query().exec())
    {
        m_id = id;
        return true;
    }
    return false;
}

bool db::CoverItem::updateSize(int size)
{
    return updateWrapper<int>("size", size, m_size);
}

bool db::CoverItem::updateCover(const QPixmap &cover)
{
    const QByteArray bytes = coverToBytes(cover);

    if (update("cover", bytes))
    {
        m_cover = cover;
        return true;
    }
    return false;
}

QByteArray db::CoverItem::coverToBytes(const QPixmap &cover)
{
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QBuffer::WriteOnly);
    cover.save(&buffer, "PNG");

    return bytes;
}

bool db::CoverItem::insert(const QByteArray &bytes)
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

bool db::CoverItem::commit(const QByteArray &bytes)
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

int db::CoverItem::lastId()
{
    query().exec("SELECT max(id) FROM covers");

    int id = 1;
    if (query().first())
        id = query().value(0).toInt();

    return id;
}

int db::CoverItem::nextId()
{
    return lastId() + 1;
}

int db::CoverItem::coverId(const QByteArray &bytes)
{
    int id = coverIdBySize(bytes);
    if (id == 0)
        id = coverIdByBlob(bytes);

    return id;
}

int db::CoverItem::coverIdBySize(const QByteArray &bytes)
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

int db::CoverItem::coverIdByBlob(const QByteArray &bytes)
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

template<typename T>
bool db::CoverItem::updateWrapper(const QString &column, const T &value, T &member)
{
    if (update(column, value))
    {
        member = value;
        return true;
    }
    return false;
}

bool db::CoverItem::getBy(const QString &column, const QVariant &value)
{
    query().prepare(
        "SELECT * FROM covers "
        "WHERE " + column + " = :value"
    );
    query().bindValue(":value", value);

    if (!query().exec() || !query().first())
        return false;

    loadFromRecord(query().record());

    return true;
}

bool db::CoverItem::update(const QString &column, const QVariant &value)
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

void db::CoverItem::loadFromRecord(const QSqlRecord &record)
{
    m_id = record.value("id").toInt();
    m_size = record.value("size").toInt();
    m_cover.loadFromData(record.value("cover").toByteArray());
}
