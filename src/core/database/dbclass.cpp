#include "dbclass.hpp"

#include "dbprovider.hpp"

DbClass::DbClass()
    : m_db(DbProvider::db())
{
    m_query = SqlQuery(m_db);
    m_query.setForwardOnly(true);
}

QSqlDatabase &DbClass::db()
{
    return m_db;
}

SqlQuery &DbClass::query()
{
    return m_query;
}
