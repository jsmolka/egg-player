#include "libraryobject.hpp"

#include <QJsonArray>
#include <QStandardPaths>
#include <QVariant>
#include <QVector>

void cfg::LibraryObject::loadObject(const QJsonObject &object)
{
    setObject(object);
}

QJsonObject cfg::LibraryObject::toObject() const
{
    return object();
}

void cfg::LibraryObject::setDefaults()
{
    setDefault("cellPadding", 10);
    setDefault("itemHeight", 50);
    setDefault("paths", QJsonArray({QStandardPaths::writableLocation(QStandardPaths::MusicLocation)}));
    setDefault("scrollBarWidth", 12);
}

void cfg::LibraryObject::setCellPadding(int padding)
{
    set("cellPadding", padding);
}

int cfg::LibraryObject::cellPadding() const
{
    return scale(get("cellPadding").toInt());
}

void cfg::LibraryObject::setItemHeight(int height)
{
    set("itemHeight", height);
}

int cfg::LibraryObject::itemHeight() const
{
    return scale(get("itemHeight").toInt());
}

void cfg::LibraryObject::setPaths(const QStrings &paths)
{
    QJsonArray array;
    for (const QString &path : paths)
        array << QJsonValue::fromVariant(path);

    set("paths", QJsonValue(array));
}

QStrings cfg::LibraryObject::paths() const
{
    QStrings paths;
    for (const QJsonValue &value : get("paths").toArray())
        paths << value.toString();

    return paths;
}

void cfg::LibraryObject::setScrollBarWidth(int width)
{
    set("scrollBarWidth", width);
}

int cfg::LibraryObject::scrollBarWidth() const
{
    return scale(get("scrollBarWidth").toInt());
}
