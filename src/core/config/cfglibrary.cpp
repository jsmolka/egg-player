#include "cfglibrary.hpp"

#include <QJsonArray>
#include <QStandardPaths>
#include <QVariant>
#include <QVector>

void cfg::Library::loadObject(const QJsonObject &object)
{
    setObject(object);
}

QJsonObject cfg::Library::toObject() const
{
    return object();
}

void cfg::Library::setDefaults()
{
    setDefault("cellPadding", 10);
    setDefault("itemHeight", 50);
    setDefault("paths", QJsonArray({QStandardPaths::writableLocation(QStandardPaths::MusicLocation)}));
    setDefault("scrollBarWidth", 12);
}

void cfg::Library::setCellPadding(int padding)
{
    set("cellPadding", padding);
}

int cfg::Library::cellPadding() const
{
    return scale(get("cellPadding").toInt());
}

void cfg::Library::setItemHeight(int height)
{
    set("itemHeight", height);
}

int cfg::Library::itemHeight() const
{
    return scale(get("itemHeight").toInt());
}

void cfg::Library::setPaths(const QStrings &paths)
{
    QJsonArray array;
    for (const QString &path : paths)
        array << QJsonValue::fromVariant(path);

    set("paths", QJsonValue(array));
}

QStrings cfg::Library::paths() const
{
    QStrings paths;
    for (const QJsonValue &value : get("paths").toArray())
        paths << value.toString();

    return paths;
}

void cfg::Library::setScrollBarWidth(int width)
{
    set("scrollBarWidth", width);
}

int cfg::Library::scrollBarWidth() const
{
    return scale(get("scrollBarWidth").toInt());
}
