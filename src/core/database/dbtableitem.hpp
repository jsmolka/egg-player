#ifndef DBTABLEITEM_HPP
#define DBTABLEITEM_HPP

#include <QVariant>

#include "dbbase.hpp"

class DbTableItem : public DbBase
{
public:
    using DbBase::DbBase;

    virtual bool exists() = 0;
    virtual bool insert() = 0;
    virtual bool commit() = 0;

protected:
    virtual bool getBy(const QVariant &column, const QVariant &value) = 0;
};

#endif // DBTABLEITEM_HPP
