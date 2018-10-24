#include "dbinitializer.hpp"

#include "cover.hpp"
#include "dbcover.hpp"

void DbInitializer::initialize()
{
    createTables();
    insertDefaultCover();
}

bool DbInitializer::tableExists(const QString &table)
{
    query().prepare(
        "SELECT 1 FROM sqlite_master "
        "WHERE name = :name"
    );
    query().bindValue(":name", table);

    return query().exec() && query().first();
}

void DbInitializer::createTables()
{
    if (!tableExists("audios"))
        createTableAudios();
    if (!tableExists("covers"))
        createTableCovers();
}

void DbInitializer::createTableAudios()
{
    query().exec(
        "CREATE TABLE IF NOT EXISTS audios("
        "  file TEXT PRIMARY KEY,"
        "  title TEXT,"
        "  artist TEXT,"
        "  album TEXT,"
        "  genre TEXT,"
        "  year INTEGER,"
        "  track INTEGER,"
        "  duration INTEGER,"
        "  coverid INTEGER,"
        "  modified INTEGER"
        ")"
    );
}

void DbInitializer::createTableCovers()
{
    query().exec(
        "CREATE TABLE IF NOT EXISTS covers("
        "  id INTEGER PRIMARY KEY,"
        "  size INTEGER,"
        "  cover BLOB"
        ")"
    );
}

void DbInitializer::dropTable(const QString &table)
{
    query().prepare("DROP TABLE IF EXISTS :table");
    query().bindValue(":table", table);
    query().exec();
}

void DbInitializer::insertDefaultCover()
{
    DbCover dbCover;
    if (!dbCover.getById(1))
    {
        const QPixmap cover = Cover::scale(QPixmap(IMG_DEFAULT_COVER), Cover::defaultSize());
        dbCover.setId(1);
        dbCover.setCover(cover);
        dbCover.insert();
    }
}
