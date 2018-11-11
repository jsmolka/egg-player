#ifndef DB_PROVIDER_HPP
#define DB_PROVIDER_HPP

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

#endif // DB_PROVIDER_HPP
