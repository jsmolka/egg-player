#ifndef SQLQUERY_HPP
#define SQLQUERY_HPP

#include <QSqlQuery>

#include "core/globals.hpp"

class SqlQuery : public QSqlQuery
{
public:
    using QSqlQuery::QSqlQuery;

    bool exec();
    bool exec(const QString &query);
    QString lastQuery() const;

private:
    void error() const;
};

#endif // SQLQUERY_HPP
