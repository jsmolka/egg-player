#ifndef CFGLIBRARY_HPP
#define CFGLIBRARY_HPP

#include <QJsonArray>
#include <QStandardPaths>
#include <QVariant>

#include "cfgabstract.hpp"
#include "types.hpp"

class CfgLibrary : public CfgAbstract
{
public:
    CfgLibrary();
    CfgLibrary(QJsonObject object);

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

#endif // CFGLIBRARY_HPP
