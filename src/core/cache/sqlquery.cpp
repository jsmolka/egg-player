#include "sqlquery.hpp"

#include <QSqlError>

#include "logger.hpp"

bool SqlQuery::exec()
{
    const bool success = QSqlQuery::exec();
    if (!success)
        error();

    return success;
}

bool SqlQuery::exec(const QString &query)
{
    const bool success = QSqlQuery::exec(query);
    if (!success)
        error();

    return success;
}

QString SqlQuery::lastQuery() const
{
    QString query = QSqlQuery::lastQuery();
    for (auto iter = boundValues().cbegin(); iter != boundValues().cend(); ++iter)
        query.replace(iter.key(), iter.value().toString());

    return query;
}

void SqlQuery::error() const
{
    const QSqlError error = lastError();
    if (error.type() == QSqlError::NoError)
        return;

    LOG("Errors \"%1\" and \"%2\" for query \"%3\"", error.databaseText(), error.driverText(), lastQuery());
}
