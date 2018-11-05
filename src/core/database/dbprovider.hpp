#ifndef DBPROVIDER_HPP
#define DBPROVIDER_HPP

#include <QSqlDatabase>

namespace db
{
class Provider
{
public:
    static QSqlDatabase db();

private:
    static QString threadConnection();
};
}

#endif // DBPROVIDER_HPP
