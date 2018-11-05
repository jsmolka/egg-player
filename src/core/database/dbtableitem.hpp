#ifndef DBTABLEITEM_HPP
#define DBTABLEITEM_HPP

#include <QSqlRecord>
#include <QVariant>

#include "core/database/dbbase.hpp"

namespace db
{
class TableItem : public Base
{
public:
    using Base::Base;

    virtual bool exists() = 0;
    virtual bool insert() = 0;
    virtual bool commit() = 0;

    virtual bool createTable() = 0;

protected:
    virtual bool getBy(const QString &column, const QVariant &value) = 0;
    virtual bool update(const QString &column, const QVariant &value) = 0;

private:
    virtual void loadFromRecord(const QSqlRecord &record) = 0;
};
}

#endif // DBTABLEITEM_HPP
