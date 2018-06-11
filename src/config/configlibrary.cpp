#include "configlibrary.hpp"

ConfigLibrary::ConfigLibrary()
{

}

ConfigLibrary::ConfigLibrary(const QJsonObject &object)
    : ConfigItem(object)
{

}

ConfigLibrary::~ConfigLibrary()
{

}

void ConfigLibrary::setDefaults()
{
    setDefault("cellPadding", 5);
    setDefault("itemHeight", 50);
    setDefault("paths", QJsonValue(QJsonArray({QStandardPaths::writableLocation(QStandardPaths::MusicLocation)})));
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

void ConfigLibrary::setPaths(const StringList &paths)
{
    QJsonArray array;
    for (const QString &path : paths)
        array << QJsonValue::fromVariant(path);

    set("paths", QJsonValue(array));
}

StringList ConfigLibrary::paths()
{
    StringList list;
    for (const QJsonValue &element : get("paths").toArray())
        list << element.toString();

    return list;
}

void ConfigLibrary::setScrollBarWidth(int width)
{
    set("scrollBarWidth", width);
}

int ConfigLibrary::scrollBarWidth()
{
    return scale(get("scrollBarWidth").toInt());
}
