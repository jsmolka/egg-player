#ifndef DBINFO_HPP
#define DBINFO_HPP

#include "core/macros.hpp"
#include "core/database/dbtableitem.hpp"

namespace db
{
class Info : public TableItem
{
public:
    Info();

    EGG_PPROP(int, id, setId, id)
    EGG_PPROP(int, version, setVerion, version)

    bool exists();
    bool insert();
    bool commit();

    bool createTable();

    bool getById(int id);
    bool getByVersion(int version);

    bool udpateId(int id);
    bool updateVersion(int version);

protected:
    bool getBy(const QString &column, const QVariant &value);
    bool update(const QString &column, const QVariant &value);

private:
    void loadFromRecord(const QSqlRecord &record);
};
}

#endif // DBINFO_HPP
