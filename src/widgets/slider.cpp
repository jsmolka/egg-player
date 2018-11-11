#include "slider.hpp"

Slider::Slider(QWidget *parent)
    : QSlider(parent)
    , m_pressed(false)
{
    init();

    connect(this, &Slider::sliderPressed, this, &Slider::onSliderPressed);
    connect(this, &Slider::sliderReleased, this, &Slider::onSliderReleased);
}

bool Slider::isPressed() const
{
    return m_pressed;
}

void Slider::wheelEvent(QWheelEvent *event)
{
    Q_UNUSED(event);
}

void Slider::onSliderPressed()
{
    m_pressed = true;
    emit sliderMoved(value());
}

void Slider::onSliderReleased()
{
    m_pressed = false;
    emit sliderValueChanged(value());
}

void Slider::init()
{
    setFocusPolicy(Qt::NoFocus);
    setOrientation(Qt::Horizontal);
    setStyle(&m_style);
}
