#ifndef DB_QUERYOBJECT_HPP
#define DB_QUERYOBJECT_HPP

#include <QSqlDatabase>

#include "core/database/sqlquery.hpp"

namespace db
{

class QueryObject
{
public:
    QueryObject();
    virtual ~QueryObject() = default;

protected:
    const SqlQuery &query() const;

    SqlQuery &query();

private:    
    static QString threadConnection();
    static QSqlDatabase threadDb();

    SqlQuery m_query;
};

}

#endif // DB_QUERYOBJECT_HPP
