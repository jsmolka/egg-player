#include "dbcover.hpp"

#include <QBuffer>
#include <QMutex>
#include <QMutexLocker>
#include <QSqlRecord>

bool DbCover::exists()
{
    query().prepare(
        "SELECT 1 FROM audios "
        "WHERE id = :id"
    );
    query().bindValue(":id", m_id);

    return query().exec() && query().first();
}

bool DbCover::insert()
{
    return insert(coverToBytes(m_cover));
}

bool DbCover::commit()
{
    return commit(coverToBytes(m_cover));
}

bool DbCover::getById(int id)
{
    return getBy("id", id);
}

bool DbCover::getBySize(int size)
{
    return getBy("size", size);
}

bool DbCover::getByCover(const QPixmap &cover)
{
    return getBy("cover", coverToBytes(cover));
}

bool DbCover::getOrInsertCover(const QPixmap &cover)
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

bool DbCover::updateId(int id)
{
    query().prepare(
        "UPDATE covers SET"
        "  id = :newid "
        "WHERE id = :id"
    );
    query().bindValue(":newid", id);
    query().bindValue(":id", m_id);

    m_id = id;

    return query().exec();
}

bool DbCover::updateSize(int size)
{
    m_size = size;

    return update("size", size);
}

bool DbCover::updateCover(const QPixmap &cover)
{
    m_cover = cover;
    const QByteArray bytes = coverToBytes(cover);

    return update("cover", bytes);
}

bool DbCover::getBy(const QString &column, const QVariant &value)
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

bool DbCover::update(const QString &column, const QVariant &value)
{
    query().prepare(
        "UPDATE covers SET"
        "  " + column + " = :value "
        "WHERE id = :file"
    );
    query().bindValue(":value", value);
    query().bindValue(":id", m_id);

    return query().exec();
}

QByteArray DbCover::coverToBytes(const QPixmap &cover)
{
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QBuffer::WriteOnly);
    cover.save(&buffer, "PNG");

    return bytes;
}

bool DbCover::insert(const QByteArray &bytes)
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

bool DbCover::commit(const QByteArray &bytes)
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

int DbCover::lastId()
{
    query().exec("SELECT max(id) FROM covers");

    int id = 1;
    if (query().first())
        id = query().value(0).toInt();

    return id;
}

int DbCover::nextId()
{
    return lastId() + 1;
}

int DbCover::coverId(const QByteArray &bytes)
{
    int id = coverIdBySize(bytes);
    if (id == 0)
        id = coverIdByBlob(bytes);

    return id;
}

int DbCover::coverIdBySize(const QByteArray &bytes)
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

int DbCover::coverIdByBlob(const QByteArray &bytes)
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

void DbCover::loadFromRecord(const QSqlRecord &record)
{
    m_id = record.value("id").toInt();
    m_size = record.value("size").toInt();
    m_cover.loadFromData(record.value("cover").toByteArray());
}
