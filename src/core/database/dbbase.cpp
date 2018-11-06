#include "dbbase.hpp"

#include "core/database/dbprovider.hpp"

db::Base::Base()
    : m_query(Provider::db())
{
    m_query.setForwardOnly(true);
}

db::Base::~Base()
{

}

SqlQuery &db::Base::query()
{
    return m_query;
}
