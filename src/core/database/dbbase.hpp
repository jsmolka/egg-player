#ifndef DBBASE_HPP
#define DBBASE_HPP

#include "core/database/sqlquery.hpp"

namespace db
{
class Base
{
public:
    Base();
    virtual ~Base() = 0;

protected:
    SqlQuery &query();

private:    
    SqlQuery m_query;
};
}

#endif // DBBASE_HPP
