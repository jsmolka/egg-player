#ifndef CONFIGLIBRARY_HPP
#define CONFIGLIBRARY_HPP

#include <QJsonArray>
#include <QStandardPaths>
#include <QVariant>

#include "configitem.hpp"
#include "types.hpp"

class ConfigLibrary : public ConfigItem
{
public:
    ConfigLibrary();
    ConfigLibrary(const QJsonObject &object);
    ~ConfigLibrary();

    void setDefaults() override;

    void setCellPadding(int padding);
    int cellPadding();

    void setItemHeight(int height);
    int itemHeight();

    void setPaths(const StringList &paths);
    StringList paths();

    void setScrollBarWidth(int width);
    int scrollBarWidth();
};

#endif // CONFIGLIBRARY_HPP
