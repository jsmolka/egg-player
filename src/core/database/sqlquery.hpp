#ifndef DB_SQLQUERY_HPP
#define DB_SQLQUERY_HPP

#include <QSqlQuery>

namespace db
{

class SqlQuery : public QSqlQuery
{
public:
    using QSqlQuery::QSqlQuery;

    bool exec();
    bool exec(const QString &query);

    QString lastQuery() const;

private:
    bool check(bool success) const;
    void error() const;
};

}

#endif // DB_SQLQUERY_HPP
