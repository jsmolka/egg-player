#ifndef DBTABLEITEM_HPP
#define DBTABLEITEM_HPP

#include <QVariant>

#include "dbclass.hpp"

class DbTableItem : public DbClass
{
public:
    using DbClass::DbClass;

    virtual bool insert() = 0;
    virtual bool commit() = 0;
    virtual bool getBy(const QVariant &column, const QVariant &value) = 0;
};

#endif // DBTABLEITEM_HPP
