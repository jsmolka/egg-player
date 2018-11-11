#include "barobject.hpp"

void cfg::bar::LabelWidthObject::loadObject(const QJsonObject &object)
{
    setObject(object);
}

QJsonObject cfg::bar::LabelWidthObject::toObject() const
{
    return object();
}

void cfg::bar::LabelWidthObject::setDefaults()
{
    setDefault("time", 50);
    setDefault("track", 240);
}

void cfg::bar::LabelWidthObject::setTime(int width)
{
    set("time", width);
}

int cfg::bar::LabelWidthObject::time() const
{
    return scale(get("time").toInt());
}

void cfg::bar::LabelWidthObject::setTrack(int width)
{
    set("time", width);
}

int cfg::bar::LabelWidthObject::track() const
{
    return scale(get("track").toInt());
}

void cfg::bar::SliderObject::loadObject(const QJsonObject &object)
{
    setObject(object);
}

QJsonObject cfg::bar::SliderObject::toObject() const
{
    return object();
}

void cfg::bar::SliderObject::setDefaults()
{
    setDefault("grooveHeight", 2);
    setDefault("handleSize", 16);
}

void cfg::bar::SliderObject::setGrooveHeight(int height)
{
    set("grooveHeight", height);
}

int cfg::bar::SliderObject::grooveHeight() const
{
    return scale(get("grooveHeight").toInt());
}

void cfg::bar::SliderObject::setHandleSize(int size)
{
    set("handleSize", size);
}

int cfg::bar::SliderObject::handleSize() const
{
    return scale(get("handleSize").toInt());
}

void cfg::BarObject::loadObject(const QJsonObject &object)
{
    setObject(object);

    m_labelWidth.loadObject(object.value("labelWidth").toObject());
    m_slider.loadObject(object.value("slider").toObject());
}

QJsonObject cfg::BarObject::toObject() const
{
    QJsonObject object = this->object();
    object.insert("labelWidth", m_labelWidth.toObject());
    object.insert("slider", m_slider.toObject());

    return object;
}

void cfg::BarObject::setDefaults()
{
    setDefault("height", 68);
    setDefault("iconSize", 32);
    setDefault("margin", 8);
    setDefault("spacing", 10);

    m_labelWidth.setDefaults();
    m_slider.setDefaults();
}

const cfg::bar::LabelWidthObject &cfg::BarObject::labelWidth() const
{
    return m_labelWidth;
}

const cfg::bar::SliderObject &cfg::BarObject::slider() const
{
    return m_slider;
}

cfg::bar::LabelWidthObject &cfg::BarObject::labelWidth()
{
    return EGG_REF_CAST(cfg::BarObject, cfg::bar::LabelWidthObject, labelWidth);
}

cfg::bar::SliderObject &cfg::BarObject::slider()
{
    return EGG_REF_CAST(cfg::BarObject, cfg::bar::SliderObject, slider);
}

void cfg::BarObject::setHeight(int height)
{
    set("height", height);
}

int cfg::BarObject::height() const
{
    return scale(get("height").toInt());
}

void cfg::BarObject::setIconSize(int size)
{
    set("iconSize", size);
}

int cfg::BarObject::iconSize() const
{
    return scale(get("iconSize").toInt());
}

void cfg::BarObject::setMargin(int margin)
{
    set("margin", margin);
}

int cfg::BarObject::margin() const
{
    return scale(get("margin").toInt());
}

void cfg::BarObject::setSpacing(int spacing)
{
    set("spacing", spacing);
}

int cfg::BarObject::spacing() const
{
    return scale(get("spacing").toInt());
}

int cfg::BarObject::coverSize() const
{
    return height() - 2 * margin();
}
