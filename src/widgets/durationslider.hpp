#ifndef DURATIONSLIDER_HPP
#define DURATIONSLIDER_HPP

#include "widgets/slider.hpp"

class DurationSlider : public Slider
{
    Q_OBJECT

public:
    explicit DurationSlider(QWidget *parent = nullptr);

private slots:
    void onReleased();
};

#endif // DURATIONSLIDER_HPP
