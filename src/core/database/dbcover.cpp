#include "dbcover.hpp"

#include <QBuffer>
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
    const QByteArray bytes = coverToBytes(m_cover);
    const int id = coverId(bytes);
    if (id != 0)
    {
        m_id = id;
        return true;
    }

    query().prepare(
        "INSERT INTO covers VALUES ("
        " :id,"
        " :size,"
        " :cover"
        ")"
    );
    query().bindValue(":id", m_id);
    query().bindValue(":size", bytes.size());
    query().bindValue(":cover", bytes);

    return query().exec();
}

bool DbCover::commit()
{
    const QByteArray bytes = coverToBytes(m_cover);

    query().prepare(
        "UPDATE covers SET"
        " size = :size"
        " cover = :cover "
        "WHERE id = :id"
    );
    query().bindValue(":size", bytes.size());
    query().bindValue(":cover", bytes);
    query().bindValue(":id", m_id);

    return query().exec();
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

bool DbCover::getBy(const QVariant &column, const QVariant &value)
{
    query().prepare(
        "SELECT * FROM covers "
        "WHERE :column = :value"
    );
    query().bindValue(":column", column);
    query().bindValue(":value", value);

    if (!query().exec())
        return false;

    if (!query().first())
        return false;

    loadFromRecord(query().record());

    return true;
}

QByteArray DbCover::coverToBytes(const QPixmap &cover)
{
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QBuffer::WriteOnly);
    cover.save(&buffer, "PNG");

    return bytes;
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
        id = query().value(0).toInt();
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
        id = query().value(0).toInt();

    return id;
}

void DbCover::loadFromRecord(const QSqlRecord &record)
{
    m_id = record.value("id").toInt();
    m_size = record.value("size").toInt();
    m_cover.loadFromData(record.value("cover").toByteArray());
}
