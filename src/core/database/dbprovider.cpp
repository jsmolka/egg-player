#include "dbprovider.hpp"

#include <QThread>

#include "constants.hpp"

QSqlDatabase DbProvider::db()
{
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
