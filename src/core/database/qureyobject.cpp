#include "queryobject.hpp"

#include "core/database/provider.hpp"

db::QueryObject::QueryObject()
    : m_query(Provider::db())
{
    m_query.setForwardOnly(true);
}

db::QueryObject::~QueryObject()
{

}

db::SqlQuery &db::QueryObject::query()
{
    return m_query;
}
