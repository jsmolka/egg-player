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
    int cellPadding() const;

    void setItemHeight(int height);
    int itemHeight() const;

    void setPaths(const Paths &paths);
    Paths paths() const;

    void setScrollBarWidth(int width);
    int scrollBarWidth() const;
};

#endif // CONFIGLIBRARY_HPP
