#ifndef CFG_LIBRARYOBJECT_HPP
#define CFG_LIBRARYOBJECT_HPP

#include "core/types.hpp"
#include "core/config/jsonobject.hpp"

namespace cfg
{

class LibraryObject : public JsonObject
{
public:
    void loadObject(const QJsonObject &object) override;
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
};

}

#endif // CFG_LIBRARYOBJECT_HPP
