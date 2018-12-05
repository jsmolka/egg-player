#include "durationslider.hpp"

DurationSlider::DurationSlider(QWidget *parent)
    : Slider(parent)
{
    connect(this, &DurationSlider::sliderReleased, this, &DurationSlider::onReleased);
}

void DurationSlider::onReleased()
{
    repaint();
}
