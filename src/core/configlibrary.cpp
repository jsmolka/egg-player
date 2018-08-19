#include "configlibrary.hpp"

#include <QJsonArray>
#include <QStandardPaths>
#include <QVariant>
#include <QVector>

void ConfigLibrary::setDefaults()
{
    setDefault("cellPadding", 5);
    setDefault("itemHeight", 50);
    setDefault("paths", QJsonArray({QStandardPaths::writableLocation(QStandardPaths::MusicLocation)}));
    setDefault("scrollBarWidth", 12);
}

void ConfigLibrary::setCellPadding(int padding)
{
    set("cellPadding", padding);
}

int ConfigLibrary::cellPadding()
{
    return scale(get("cellPadding").toInt());
}

void ConfigLibrary::setItemHeight(int height)
{
    set("itemHeight", height);
}

int ConfigLibrary::itemHeight()
{
    return scale(get("itemHeight").toInt());
}

void ConfigLibrary::setPaths(const Files &paths)
{
    QJsonArray array;
    for (const Path &path : paths)
        array << QJsonValue::fromVariant(path);

    set("paths", QJsonValue(array));
}

Files ConfigLibrary::paths()
{
    Files paths;
    for (const QJsonValue &element : get("paths").toArray())
        paths << element.toString();

    return paths;
}

void ConfigLibrary::setScrollBarWidth(int width)
{
    set("scrollBarWidth", width);
}

int ConfigLibrary::scrollBarWidth()
{
    return scale(get("scrollBarWidth").toInt());
}
