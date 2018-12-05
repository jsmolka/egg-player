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

    EGG_P_PROP(int, id, setId, id)
    EGG_P_PROP(int, version, setVersion, version)

    bool exists();
    bool insert();
    bool commit();

    bool createTable();

    bool getById(int id);
    bool getByVersion(int version);

    bool udpateId(int id);
    bool updateVersion(int version);

private:
    template <typename T>
    bool updateWrapper(const QString &column, const T &value, T &member);

    bool getBy(const QString &column, const QVariant &value);
    bool update(const QString &column, const QVariant &value);
    void loadFromRecord(const QSqlRecord &record);
};

}

#endif // DB_INFO_HPP
