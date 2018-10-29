#include "dbbase.hpp"

#include "core/database/dbprovider.hpp"

DbBase::DbBase()
    : DbBase(DbProvider::db())
{

}

DbBase::DbBase(QSqlDatabase db)
    : m_query(db)
{
    m_query.setForwardOnly(true);
}

SqlQuery &DbBase::query()
{
    return m_query;
}
