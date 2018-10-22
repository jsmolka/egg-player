#ifndef DBCLASS_HPP
#define DBCLASS_HPP

#include <QSqlDatabase>

#include "sqlquery.hpp"

class DbClass
{
public:
    DbClass();

protected:
    QSqlDatabase &db();
    SqlQuery &query();

private:
    QSqlDatabase m_db;
    SqlQuery m_query;
};

#endif // DBCLASS_HPP
