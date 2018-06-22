#include "slider.hpp"

Slider::Slider(QWidget *parent)
    : QSlider(parent)
    , m_pressed(false)
{
    setup();

    connect(this, SIGNAL(sliderPressed()), this, SLOT(onSliderPressed()));
    connect(this, SIGNAL(sliderReleased()), this, SLOT(onSliderReleased()));
}

Slider::~Slider()
{

}

bool Slider::isPressed() const
{
    return m_pressed;
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
    setStyle(new ClickableStyle(style()));
}
