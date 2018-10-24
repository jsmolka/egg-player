#include "dbprovider.hpp"

#include <QSqlQuery>
#include <QThread>

#include "constants.hpp"
#include "logger.hpp"

QSqlDatabase DbProvider::db()
{
    if (!QSqlDatabase::isDriverAvailable("QSQLITE"))
        LOG("QSQLITE driver not available");

    const QString connection = threadConnection();
    if (!QSqlDatabase::contains(connection))
        QSqlDatabase::addDatabase("QSQLITE", connection);

    QSqlDatabase db = QSqlDatabase::database(connection, false);
    db.setDatabaseName(SQL_PATH);
    db.open();

    return db;
}

QString DbProvider::threadConnection()
{
    return SQL_CONNECTION + QString::number(reinterpret_cast<quint64>(QThread::currentThread()), 16);
}
