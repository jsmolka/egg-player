#include "lengthslider.hpp"

LengthSlider::LengthSlider(QWidget *parent) : QSlider(parent)
{
    setOrientation(Qt::Horizontal);
    setStyle(new LengthSliderStyle(style()));

    m_pressed = false;
    m_value = 0;

    connect(this, SIGNAL(sliderPressed()), this, SLOT(onSliderPressed()));
    connect(this, SIGNAL(sliderReleased()), this, SLOT(onSliderReleased()));
    connect(this, SIGNAL(sliderMoved(int)), this, SLOT(onSliderMoved(int)));
}

LengthSlider::~LengthSlider()
{

}

bool LengthSlider::isPressed() const
{
    return m_pressed;
}

void LengthSlider::onSliderPressed()
{
    m_pressed = true;
    m_value = value();
}

void LengthSlider::onSliderReleased()
{
    m_pressed = false;
    emit positionChanged(m_value);
}

void LengthSlider::onSliderMoved(int value)
{
    m_value = value;
}
