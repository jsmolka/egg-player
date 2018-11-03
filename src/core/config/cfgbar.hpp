#ifndef CFGBAR_HPP
#define CFGBAR_HPP

#include "core/config/cfgbarlabelwidth.hpp"
#include "core/config/cfgbarslider.hpp"
#include "core/config/cfgbase.hpp"

namespace cfg
{
class Bar : public Base
{
public:
    void loadObject(const QJsonObject &object) override;
    QJsonObject toObject() const override;

    void setDefaults() override;

    bar::LabelWidth &labelWidth();
    bar::Slider &slider();

    void setHeight(int height);
    int height() const;

    void setIconSize(int size);
    int iconSize() const;

    void setMargin(int margin);
    int margin() const;

    void setSpacing(int spacing);
    int spacing() const;

    int coverSize() const;

private:
    bar::LabelWidth m_labelWidth;
    bar::Slider m_slider;
};
}

#endif // CFGBAR_HPP
