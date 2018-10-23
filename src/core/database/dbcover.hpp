#ifndef DBCOVER_HPP
#define DBCOVER_HPP

#include <QByteArray>
#include <QPixmap>
#include <QSqlRecord>

#include "dbtableitem.hpp"
#include "globals.hpp"

class DbCover : public DbTableItem
{
public:
    using DbTableItem::DbTableItem;

    EGG_PPROP(int, id, setId, id)
    EGG_PPROP(int, size, setSize, size)
    EGG_CPROP(QPixmap, cover, setCover, cover)

    bool exists();
    bool insert();
    bool commit();

    bool getById(int id);
    bool getBySize(int size);
    bool getByCover(const QPixmap &cover);
    bool getOrInsertCover(const QPixmap &cover);

protected:
    bool getBy(const QVariant &column, const QVariant &value);

private:
    static QByteArray coverToBytes(const QPixmap &cover);

    bool insert(const QByteArray &bytes);
    bool commit(const QByteArray &bytes);

    int lastId();
    int nextId();

    int coverId(const QByteArray &bytes);
    int coverIdBySize(const QByteArray &bytes);
    int coverIdByBlob(const QByteArray &bytes);
    void loadFromRecord(const QSqlRecord &record);
};

#endif // DBCOVER_HPP
