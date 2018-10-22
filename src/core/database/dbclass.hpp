#ifndef DBCLASS_HPP
#define DBCLASS_HPP

#include <QSqlDatabase>

#include "sqlquery.hpp"

class DbClass
{
public:
    DbClass();
    virtual ~DbClass() = default;

protected:
    QSqlDatabase &db();
    SqlQuery &query();

private:
    QSqlDatabase m_db;
    SqlQuery m_query;
};

#endif // DBCLASS_HPP
