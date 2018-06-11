#include "cfglibrary.hpp"

CfgLibrary::CfgLibrary()
{

}

CfgLibrary::CfgLibrary(QJsonObject object)
    : CfgAbstract(object)
{

}

void CfgLibrary::setDefaults()
{
    setDefault("cellPadding", 5);
    setDefault("itemHeight", 50);
    setDefault("paths", QJsonValue(QJsonArray({QStandardPaths::writableLocation(QStandardPaths::MusicLocation)})));
    setDefault("scrollBarWidth", 12);
}

void CfgLibrary::setCellPadding(int padding)
{
    m_object.insert("cellPadding", padding);
}

int CfgLibrary::cellPadding()
{
    return scale(m_object.value("cellPadding").toInt());
}

void CfgLibrary::setItemHeight(int height)
{
    m_object.insert("itemHeight", height);
}

int CfgLibrary::itemHeight()
{
    return scale(m_object.value("itemHeight").toInt());
}

void CfgLibrary::setPaths(const StringList &paths)
{
    QJsonArray array;
    for (const QString &path : paths)
        array << QJsonValue::fromVariant(path);

    m_object.insert("paths", QJsonValue(array));
}

StringList CfgLibrary::paths()
{
    StringList list;
    for (const QJsonValue &element : m_object.value("paths").toArray())
        list << element.toString();

    return list;
}

void CfgLibrary::setScrollBarWidth(int width)
{
    m_object.insert("scrollBarWidth", width);
}

int CfgLibrary::scrollBarWidth()
{
    return scale(m_object.value("scrollBarWidth").toInt());
}
