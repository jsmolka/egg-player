#ifndef CONFIGLIBRARY_HPP
#define CONFIGLIBRARY_HPP

#include "configabstract.hpp"
#include "types.hpp"

class ConfigLibrary : public ConfigAbstract
{
public:
    using ConfigAbstract::ConfigAbstract;

    void setDefaults() override;

    void setCellPadding(int padding);
    int cellPadding();

    void setItemHeight(int height);
    int itemHeight();

    void setPaths(const Files &paths);
    Files paths();

    void setScrollBarWidth(int width);
    int scrollBarWidth();
};

#endif // CONFIGLIBRARY_HPP
