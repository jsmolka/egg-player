#ifndef DB_TABLEITEM_HPP
#define DB_TABLEITEM_HPP

#include <QSqlRecord>
#include <QVariant>

#include "core/database/queryobject.hpp"

namespace db
{

class TableItem : public QueryObject
{
public:
    using QueryObject::QueryObject;

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

#endif // DB_TABLEITEM_HPP
