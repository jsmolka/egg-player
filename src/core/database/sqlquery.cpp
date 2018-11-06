#include "sqlquery.hpp"

#include <QMapIterator>
#include <QSqlError>

#include "core/logger.hpp"

bool SqlQuery::exec()
{
    return check(QSqlQuery::exec());
}

bool SqlQuery::exec(const QString &query)
{
    return check(QSqlQuery::exec(query));
}

QString SqlQuery::lastQuery() const
{
    QString query = QSqlQuery::lastQuery();
    QMapIterator<QString, QVariant> iter(boundValues());
    while (iter.hasNext())
    {
        iter.next();
        query.replace(iter.key(), iter.value().toString());
    }
    return query;
}

bool SqlQuery::check(bool success) const
{
   if (!success)
       error();

   return success;
}

void SqlQuery::error() const
{
    const QSqlError error = lastError();
    if (!error.isValid() || error.type() == QSqlError::NoError)
        return;

    EGG_LOG("Errors \"%1\" and \"%2\" for query \"%3\"", error.databaseText(), error.driverText(), lastQuery());
}
