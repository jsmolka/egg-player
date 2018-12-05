#include "barjson.hpp"

void cfg::LabelWidthJson::loadFromObject(const QJsonObject &object)
{
    setObject(object);
}

QJsonObject cfg::LabelWidthJson::toObject() const
{
    return object();
}

void cfg::LabelWidthJson::setDefaults()
{
    setDefault("time", 50);
    setDefault("track", 200);
}

void cfg::LabelWidthJson::setTime(int width)
{
    set("time", width);
}

int cfg::LabelWidthJson::time() const
{
    return scale(get("time").toInt());
}

void cfg::LabelWidthJson::setTrack(int width)
{
    set("time", width);
}

int cfg::LabelWidthJson::track() const
{
    return scale(get("track").toInt());
}

void cfg::SliderJson::loadFromObject(const QJsonObject &object)
{
    setObject(object);
}

QJsonObject cfg::SliderJson::toObject() const
{
    return object();
}

void cfg::SliderJson::setDefaults()
{
    setDefault("grooveHeight", 2);
    setDefault("handleSize", 16);
}

void cfg::SliderJson::setGrooveHeight(int height)
{
    set("grooveHeight", height);
}

int cfg::SliderJson::grooveHeight() const
{
    return scale(get("grooveHeight").toInt());
}

void cfg::SliderJson::setHandleSize(int size)
{
    set("handleSize", size);
}

int cfg::SliderJson::handleSize() const
{
    return scale(get("handleSize").toInt());
}

void cfg::BarJson::loadFromObject(const QJsonObject &object)
{
    setObject(object);

    m_labelWidth.loadFromObject(object.value("labelWidth").toObject());
    m_slider.loadFromObject(object.value("slider").toObject());
}

QJsonObject cfg::BarJson::toObject() const
{
    QJsonObject object = this->object();
    object.insert("labelWidth", m_labelWidth.toObject());
    object.insert("slider", m_slider.toObject());

    return object;
}

void cfg::BarJson::setDefaults()
{
    setDefault("height", 68);
    setDefault("iconSize", 32);
    setDefault("margin", 8);
    setDefault("spacing", 10);

    m_labelWidth.setDefaults();
    m_slider.setDefaults();
}

const cfg::LabelWidthJson &cfg::BarJson::labelWidth() const
{
    return m_labelWidth;
}

cfg::LabelWidthJson &cfg::BarJson::labelWidth()
{
    return EGG_REF_CAST(cfg::BarJson, cfg::LabelWidthJson, labelWidth);
}

const cfg::SliderJson &cfg::BarJson::slider() const
{
    return m_slider;
}

cfg::SliderJson &cfg::BarJson::slider()
{
    return EGG_REF_CAST(cfg::BarJson, cfg::SliderJson, slider);
}

void cfg::BarJson::setHeight(int height)
{
    set("height", height);
}

int cfg::BarJson::height() const
{
    return scale(get("height").toInt());
}

void cfg::BarJson::setIconSize(int size)
{
    set("iconSize", size);
}

int cfg::BarJson::iconSize() const
{
    return scale(get("iconSize").toInt());
}

void cfg::BarJson::setMargin(int margin)
{
    set("margin", margin);
}

int cfg::BarJson::margin() const
{
    return scale(get("margin").toInt());
}

void cfg::BarJson::setSpacing(int spacing)
{
    set("spacing", spacing);
}

int cfg::BarJson::spacing() const
{
    return scale(get("spacing").toInt());
}

int cfg::BarJson::coverSize() const
{
    return height() - 2 * margin();
}
