#include "queryobject.hpp"

#include <QThread>

#include "core/constants.hpp"
#include "core/logger.hpp"
#include "core/macros.hpp"

db::QueryObject::QueryObject()
    : m_query(threadDb())
{
    m_query.setForwardOnly(true);
}

const db::SqlQuery &db::QueryObject::query() const
{
    return m_query;
}

db::SqlQuery &db::QueryObject::query()
{
    return EGG_REF_CAST(db::QueryObject, db::SqlQuery, query);
}

QString db::QueryObject::threadConnection()
{
    return constants::db::Connection + QString::number(
        reinterpret_cast<quint64>(QThread::currentThread()), 16);
}

QSqlDatabase db::QueryObject::threadDb()
{
    if (!QSqlDatabase::isDriverAvailable("QSQLITE"))
        egg_log() << "QSQLITE driver not available";

    const QString connection = threadConnection();
    if (!QSqlDatabase::contains(connection))
        QSqlDatabase::addDatabase("QSQLITE", connection);

    QSqlDatabase db = QSqlDatabase::database(connection, false);
    db.setDatabaseName(constants::db::File);
    db.open();

    return db;
}
