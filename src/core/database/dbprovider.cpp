#include "dbprovider.hpp"

#include <QThread>

#include "core/constants.hpp"
#include "core/logger.hpp"

QSqlDatabase db::Provider::db()
{
    if (!QSqlDatabase::isDriverAvailable("QSQLITE"))
        EGG_LOG("QSQLITE driver not available");

    const QString connection = threadConnection();
    if (!QSqlDatabase::contains(connection))
        QSqlDatabase::addDatabase("QSQLITE", connection);

    QSqlDatabase db = QSqlDatabase::database(connection, false);
    db.setDatabaseName(constants::db::file);
    if (!db.open())
        EGG_LOG("Cannot open database");

    return db;
}

QString db::Provider::threadConnection()
{
    return constants::db::connection + QString::number(reinterpret_cast<quint64>(QThread::currentThread()), 16);
}
