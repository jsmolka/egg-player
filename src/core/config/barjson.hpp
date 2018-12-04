#ifndef CFG_BARJSON_HPP
#define CFG_BARJSON_HPP

#include "core/config/jsonobject.hpp"

namespace cfg
{

namespace bar
{

class LabelWidthJson : public JsonObject
{
public:
    void loadFromObject(const QJsonObject &object) override;
    QJsonObject toObject() const override;

    void setDefaults() override;

    void setTime(int width);
    int time() const;

    void setTrack(int width);
    int track() const;
};

class SliderJson : public JsonObject
{
public:
    void loadFromObject(const QJsonObject &object) override;
    QJsonObject toObject() const override;

    void setDefaults() override;

    void setGrooveHeight(int height);
    int grooveHeight() const;

    void setHandleSize(int size);
    int handleSize() const;
};

}

class BarJson : public JsonObject
{
public:
    void loadFromObject(const QJsonObject &object) override;
    QJsonObject toObject() const override;

    void setDefaults() override;

    const bar::LabelWidthJson &labelWidth() const;
    const bar::SliderJson &slider() const;

    bar::LabelWidthJson &labelWidth();
    bar::SliderJson &slider();

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
    bar::LabelWidthJson m_labelWidth;
    bar::SliderJson m_slider;
};

}

#endif // CFG_BARJSON_HPP
