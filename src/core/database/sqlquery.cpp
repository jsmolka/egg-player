#include "sqlquery.hpp"

#include <QMapIterator>
#include <QSqlError>

#include "core/logger.hpp"

bool db::SqlQuery::exec()
{
    return check(QSqlQuery::exec());
}

bool db::SqlQuery::exec(const QString &query)
{
    return check(QSqlQuery::exec(query));
}

QString db::SqlQuery::boundLastQuery() const
{
    QString query = lastQuery();
    QMapIterator<QString, QVariant> iter(boundValues());
    while (iter.hasNext())
    {
        iter.next();
        query.replace(iter.key(), iter.value().toString());
    }
    return query;
}

bool db::SqlQuery::check(bool success) const
{
   if (!success)
       error();

   return success;
}

void db::SqlQuery::error() const
{
    const QSqlError error = lastError();
    if (!error.isValid() || error.type() == QSqlError::NoError)
        return;

    egg_log() << QString("Errors \"%1\" and \"%2\" for query \"%3\"").arg(error.databaseText(), error.driverText(), boundLastQuery());
}
