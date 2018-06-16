#include "clickableslider.hpp"

ClickableSlider::ClickableSlider(QWidget *parent)
    : QSlider(parent)
    , m_pressed(false)
{
    setup();

    connect(this, SIGNAL(sliderPressed()), this, SLOT(onSliderPressed()));
    connect(this, SIGNAL(sliderReleased()), this, SLOT(onSliderReleased()));
}

ClickableSlider::~ClickableSlider()
{

}

bool ClickableSlider::isPressed() const
{
    return m_pressed;
}

void ClickableSlider::onSliderPressed()
{
    m_pressed = true;
    emit sliderMoved(value());
}

void ClickableSlider::onSliderReleased()
{
    m_pressed = false;
    emit sliderValueChanged(value());
}

void ClickableSlider::setup()
{
    setFocusPolicy(Qt::NoFocus);
    setOrientation(Qt::Horizontal);
    setStyle(new ClickableStyle(style()));
}
