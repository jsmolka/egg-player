#ifndef CFGLIBRARY_HPP
#define CFGLIBRARY_HPP

#include "core/types.hpp"
#include "core/config/cfgbase.hpp"

namespace cfg
{
class Library : public Base
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

#endif // CFGLIBRARY_HPP
