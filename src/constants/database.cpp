#include "database.hpp"

const QString SQL_DB_NAME      = "cache.db";
const QString SQL_CREATE_TABLE = "CREATE TABLE IF NOT EXISTS cache (file TEXT, cover BLOB)";
const QString SQL_INSERT       = "INSERT INTO cache (file, cover) VALUES (:FILE, :COVER)";
const QString SQL_RETRIEVE     = "SELECT cover FROM cache WHERE file = :FILE";
