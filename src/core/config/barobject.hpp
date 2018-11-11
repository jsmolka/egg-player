#ifndef CFG_BAROBJECT_HPP
#define CFG_BAROBJECT_HPP

#include "core/config/jsonobject.hpp"

namespace cfg
{

namespace bar
{

class LabelWidthObject : public JsonObject
{
public:
    void loadObject(const QJsonObject &object) override;
    QJsonObject toObject() const override;

    void setDefaults() override;

    void setTime(int width);
    int time() const;

    void setTrack(int width);
    int track() const;
};

class SliderObject : public JsonObject
{
public:
    void loadObject(const QJsonObject &object) override;
    QJsonObject toObject() const override;

    void setDefaults() override;

    void setGrooveHeight(int height);
    int grooveHeight() const;

    void setHandleSize(int size);
    int handleSize() const;
};

}

class BarObject : public JsonObject
{
public:
    void loadObject(const QJsonObject &object) override;
    QJsonObject toObject() const override;

    void setDefaults() override;

    const bar::LabelWidthObject &labelWidth() const;
    const bar::SliderObject &slider() const;

    bar::LabelWidthObject &labelWidth();
    bar::SliderObject &slider();

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
    bar::LabelWidthObject m_labelWidth;
    bar::SliderObject m_slider;
};

}

#endif // CFG_BAROBJECT_HPP
