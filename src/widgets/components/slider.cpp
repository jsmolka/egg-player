#include "slider.hpp"

#include "clickablestyle.hpp"

Slider::Slider(QWidget *parent)
    : QSlider(parent)
    , m_pressed(false)
{
    setup();

    connect(this, &Slider::sliderPressed, this, &Slider::onSliderPressed);
    connect(this, &Slider::sliderReleased, this, &Slider::onSliderReleased);
}

Slider::~Slider()
{

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

void Slider::setup()
{
    setFocusPolicy(Qt::NoFocus);
    setOrientation(Qt::Horizontal);
    setStyle(new ClickableStyle);
}
