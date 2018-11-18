#ifndef DB_INFO_HPP
#define DB_INFO_HPP

#include "core/macros.hpp"
#include "core/database/tableitem.hpp"

namespace db
{

class InfoItem : public TableItem
{
public:
    InfoItem();

    EGG_PPROP(int, id, setId, id)
    EGG_PPROP(int, version, setVersion, version)

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

#endif // DB_INFO_HPP
