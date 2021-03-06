#ifndef CFG_LIBRARYJSON_HPP
#define CFG_LIBRARYJSON_HPP

#include "core/types.hpp"
#include "core/config/jsonobject.hpp"

namespace cfg
{

class LibraryJson : public JsonObject
{
public:
    void loadFromObject(const QJsonObject &object) override;
    QJsonObject toObject() const override;

    void setDefaults() override;

    void setCellPadding(int padding);
    int cellPadding() const;

    void setItemHeight(int height);
    int itemHeight() const;

    void setPaths(const QStrings &paths);
    QStrings paths() const;

    void setScrollBarWidth(int width);
    int scrollBarWidth() const;

    void setSmoothScrolling(bool smooth);
    bool smoothScrolling() const;
};

}

#endif // CFG_LIBRARYJSON_HPP
