#include "infoitem.hpp"

db::InfoItem::InfoItem()
    : m_id(0)
    , m_version(0)
{

}

bool db::InfoItem::exists()
{
    query().prepare(
        "SELECT 1 FROM infos "
        "WHERE id = :id"
    );
    query().bindValue(":id", m_id);

    return query().exec() && query().first();
}

bool db::InfoItem::insert()
{
    query().prepare(
        "INSERT INTO infos VALUES ("
        "  :id,"
        "  :version"
        ")"
    );
    query().bindValue(":id", m_id);
    query().bindValue(":version", m_version);

    return query().exec();
}

bool db::InfoItem::commit()
{
    query().prepare(
        "UPDATE infos SET"
        "  version = :version"
        "WHERE id = :id"
    );
    query().bindValue(":id", m_id);
    query().bindValue(":version", m_version);

    return query().exec();
}

bool db::InfoItem::createTable()
{
    return query().exec(
        "CREATE TABLE IF NOT EXISTS infos ("
        "  id INTEGER PRIMARY KEY,"
        "  version INTEGER"
        ")"
    );
}

bool db::InfoItem::getById(int id)
{
    return getBy("id", id);
}

bool db::InfoItem::getByVersion(int version)
{
    return getBy("version", version);
}

bool db::InfoItem::udpateId(int id)
{
    query().prepare(
        "UPDATE infos SET"
        "  id = :newid, "
        "WHERE id = :id"
    );
    query().bindValue(":id", m_id);
    query().bindValue(":newid", id);

    m_id = id;

    return query().exec();
}

bool db::InfoItem::updateVersion(int version)
{
    m_version = version;

    return update("version", version);
}

bool db::InfoItem::getBy(const QString &column, const QVariant &value)
{
    query().prepare(
        "SELECT * FROM infos "
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

bool db::InfoItem::update(const QString &column, const QVariant &value)
{
    query().prepare(
        "UPDATE infos SET"
        "  " + column + " = :value "
        "WHERE id = :id"
    );
    query().bindValue(":file", m_id);
    query().bindValue(":value", value);

    return query().exec();
}

void db::InfoItem::loadFromRecord(const QSqlRecord &record)
{
    m_id = record.value("id").toInt();
    m_version = record.value("version").toInt();
}
