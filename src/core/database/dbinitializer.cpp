#include "dbinitializer.hpp"

#include <QFileInfo>
#include <QVariant>

#include "constants.hpp"

void DbInitializer::initialize()
{
    if (!QFileInfo(SQL_PATH).exists())
        createTables();


}

void DbInitializer::createTables()
{
    createTableAudios();
    createTableCovers();
}

void DbInitializer::createTableAudios()
{
    query().exec(
        "CREATE TABLE IF NOT EXISTS audios("
        " file TEXT PRIMARY KEY,"
        " title TEXT,"
        " artist TEXT,"
        " album TEXT,"
        " genre TEXT,"
        " year INTEGER,"
        " track INTEGER,"
        " duration INTEGER,"
        " coverid INTEGER,"
        " modified INTEGER"
        ")"
    );
}

void DbInitializer::createTableCovers()
{
    query().exec(
        "CREATE TABLE IF NOT EXISTS covers("
        " id INTEGER PRIMARY KEY,"
        " size INTEGER,"
        " cover BLOB"
        ")"
    );
}

void DbInitializer::dropTable(const QString &table)
{
    query().prepare("DROP TABLE IF EXISTS :table");
    query().bindValue(":table", QVariant(table));
}
