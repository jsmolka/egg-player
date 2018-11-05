#include "dbbase.hpp"

#include "core/database/dbprovider.hpp"

db::Base::Base()
    : Base(Provider::db())
{

}

db::Base::Base(QSqlDatabase db)
    : m_query(db)
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
