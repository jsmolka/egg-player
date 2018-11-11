#ifndef DB_QUERYOBJECT_HPP
#define DB_QUERYOBJECT_HPP

#include "core/database/sqlquery.hpp"

namespace db
{

class QueryObject
{
public:
    QueryObject();
    virtual ~QueryObject() = 0;

protected:
    SqlQuery &query();

private:    
    SqlQuery m_query;
};

}

#endif // DB_QUERYOBJECT_HPP
