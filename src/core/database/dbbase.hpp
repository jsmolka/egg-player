#ifndef DBBASE_HPP
#define DBBASE_HPP

#include <QSqlDatabase>

#include "sqlquery.hpp"

class DbBase
{
public:
    DbBase();
    virtual ~DbBase() = default;

protected:
    QSqlDatabase &db();
    SqlQuery &query();

private:    
    QSqlDatabase m_db;
    SqlQuery m_query;
};

#endif // DBBASE_HPP
