#include "dbbase.hpp"

#include "core/database/dbprovider.hpp"

DbBase::DbBase()
    : m_db(DbProvider::db())
{
    m_query = SqlQuery(m_db);
    m_query.setForwardOnly(true);
}

QSqlDatabase &DbBase::db()
{
    return m_db;
}

SqlQuery &DbBase::query()
{
    return m_query;
}
