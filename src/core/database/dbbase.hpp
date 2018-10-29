#ifndef DBBASE_HPP
#define DBBASE_HPP

#include <QSqlDatabase>

#include "core/database/sqlquery.hpp"

class DbBase
{
public:
    explicit DbBase();
    explicit DbBase(QSqlDatabase db);
    virtual ~DbBase() = default;

protected:
    SqlQuery &query();

private:    
    SqlQuery m_query;
};

#endif // DBBASE_HPP
