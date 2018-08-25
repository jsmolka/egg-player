#ifndef CONFIGLIBRARY_HPP
#define CONFIGLIBRARY_HPP

#include "configitem.hpp"
#include "types.hpp"

class ConfigLibrary : public ConfigItem
{
public:
    using ConfigItem::ConfigItem;

    void setDefaults() override;

    void setCellPadding(int padding);
    int cellPadding();

    void setItemHeight(int height);
    int itemHeight();

    void setPaths(const Paths &paths);
    Paths paths();

    void setScrollBarWidth(int width);
    int scrollBarWidth();
};

#endif // CONFIGLIBRARY_HPP
