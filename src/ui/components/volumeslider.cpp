#include "volumeslider.hpp"

VolumeSlider::VolumeSlider(QWidget *parent) :
    QWidget(parent)
{
    //setFixedSize(5 * Config::Bar::iconSize() + 4 * Config::Bar::spacing(), Config::Bar::height());

    pm_slider = new QSlider(Qt::Horizontal, this);
    pm_slider->setRange(0, 100);
    pm_slider->setValue(Player::instance()->volume());
    pm_slider->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
    setFixedWidth(5 * Config::Bar::iconSize() + 4 * Config::Bar::spacing());

    pm_slider->setFixedWidth(width() - 2 * Config::Bar::spacing());

    //setAutoFillBackground(true);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(pm_slider, 0, 0, Qt::AlignCenter);
    setLayout(layout);
}

void VolumeSlider::pop()
{
    //calcPosition();
    setVisible(true);
    raise();
}

void VolumeSlider::unpop()
{
    setVisible(false);
}
