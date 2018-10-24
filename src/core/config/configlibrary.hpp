#ifndef CONFIGLIBRARY_HPP
#define CONFIGLIBRARY_HPP

#include "core/types.hpp"
#include "core/config/configitem.hpp"

class ConfigLibrary : public ConfigItem
{
public:
    using ConfigItem::ConfigItem;

    void setDefaults() override;

    void setCellPadding(int padding);
    int cellPadding() const;

    void setItemHeight(int height);
    int itemHeight() const;

    void setPaths(const QStrings &paths);
    QStrings paths() const;

    void setScrollBarWidth(int width);
    int scrollBarWidth() const;
};

#endif // CONFIGLIBRARY_HPP
