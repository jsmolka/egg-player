#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <QSqlDatabase>

#include "sqlquery.hpp"

class Database
{
public:
    Database();

    QSqlDatabase db();
    SqlQuery &query();

private:
    static QString dbName();

    QSqlDatabase m_db;
    SqlQuery m_query;
};

#endif // DATABASE_HPP
