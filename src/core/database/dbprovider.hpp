#ifndef DBPROVIDER_HPP
#define DBPROVIDER_HPP

#include <QSqlDatabase>

#include "core/globals.hpp"

class DbProvider
{
public:
    static QSqlDatabase db();

private:
    static QString threadConnection();
};

#endif // DBPROVIDER_HPP
