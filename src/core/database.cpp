#include "database.hpp"

#include <QThread>

#include "constants.hpp"

Database::Database()
{
    if (!QSqlDatabase::contains(dbName()))
        QSqlDatabase::addDatabase("QSQLITE", dbName());

    m_db = QSqlDatabase::database(dbName(), false);
    m_db.setDatabaseName(SQL_PATH);
    m_db.open();

    m_query = SqlQuery(m_db);
    m_query.setForwardOnly(true);
}

QSqlDatabase Database::db()
{
    return m_db;
}

SqlQuery &Database::query()
{
    return m_query;
}

QString Database::dbName()
{
    return SQL_CONNECTION + QString::number(reinterpret_cast<quint64>(QThread::currentThread()), 16);
}
