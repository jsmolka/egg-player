#include "cfgbar.hpp"

void cfg::Bar::loadObject(const QJsonObject &object)
{
    setObject(object);

    m_labelWidth.loadObject(object.value("labelWidth").toObject());
    m_slider.loadObject(object.value("slider").toObject());
}

QJsonObject cfg::Bar::toObject() const
{
    QJsonObject object(this->object());
    object.insert("labelWidth", m_labelWidth.toObject());
    object.insert("slider", m_slider.toObject());

    return object;
}

void cfg::Bar::setDefaults()
{
    setDefault("height", 68);
    setDefault("iconSize", 32);
    setDefault("margin", 8);
    setDefault("spacing", 10);

    m_labelWidth.setDefaults();
    m_slider.setDefaults();
}

const cfg::bar::LabelWidth &cfg::Bar::labelWidth() const
{
    return m_labelWidth;
}

const cfg::bar::Slider &cfg::Bar::slider() const
{
    return m_slider;
}

cfg::bar::LabelWidth &cfg::Bar::labelWidth()
{
    return EGG_REF_CAST(cfg::Bar, cfg::bar::LabelWidth, labelWidth);
}

cfg::bar::Slider &cfg::Bar::slider()
{
    return EGG_REF_CAST(cfg::Bar, cfg::bar::Slider, slider);
}

void cfg::Bar::setHeight(int height)
{
    set("height", height);
}

int cfg::Bar::height() const
{
    return scale(get("height").toInt());
}

void cfg::Bar::setIconSize(int size)
{
    set("iconSize", size);
}

int cfg::Bar::iconSize() const
{
    return scale(get("iconSize").toInt());
}

void cfg::Bar::setMargin(int margin)
{
    set("margin", margin);
}

int cfg::Bar::margin() const
{
    return scale(get("margin").toInt());
}

void cfg::Bar::setSpacing(int spacing)
{
    set("spacing", spacing);
}

int cfg::Bar::spacing() const
{
    return scale(get("spacing").toInt());
}

int cfg::Bar::coverSize() const
{
    return height() - 2 * margin();
}
