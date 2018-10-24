#include "configlibrary.hpp"

#include <QJsonArray>
#include <QStandardPaths>
#include <QVariant>
#include <QVector>

void ConfigLibrary::setDefaults()
{
    setDefault("cellPadding", 10);
    setDefault("itemHeight", 50);
    setDefault("paths", QJsonArray({QStandardPaths::writableLocation(QStandardPaths::MusicLocation)}));
    setDefault("scrollBarWidth", 12);
}

void ConfigLibrary::setCellPadding(int padding)
{
    set("cellPadding", padding);
}

int ConfigLibrary::cellPadding() const
{
    return scale(get("cellPadding").toInt());
}

void ConfigLibrary::setItemHeight(int height)
{
    set("itemHeight", height);
}

int ConfigLibrary::itemHeight() const
{
    return scale(get("itemHeight").toInt());
}

void ConfigLibrary::setPaths(const QStrings &paths)
{
    QJsonArray array;
    for (const QString &path : paths)
        array << QJsonValue::fromVariant(path);

    set("paths", QJsonValue(array));
}

QStrings ConfigLibrary::paths() const
{
    QStrings paths;
    const QJsonArray array = get("paths").toArray();
    for (const QJsonValue &value : array)
        paths << value.toString();

    return paths;
}

void ConfigLibrary::setScrollBarWidth(int width)
{
    set("scrollBarWidth", width);
}

int ConfigLibrary::scrollBarWidth() const
{
    return scale(get("scrollBarWidth").toInt());
}
