#include "database.hpp"

const QString SQL_DB_NAME      = "cache.db";
const QString SQL_CREATE_TABLE = "CREATE TABLE IF NOT EXISTS cache (artist TEXT, album TEXT, cover BLOB)";
const QString SQL_INSERT       = "INSERT INTO cache (artist, album, cover) VALUES (:ARTIST, :ALBUM, :COVER)";
const QString SQL_RETRIEVE     = "SELECT cover FROM cache WHERE artist = :ARTIST AND album = :ALBUM";
