#ifndef CLICKABLESLIDER_HPP
#define CLICKABLESLIDER_HPP

#include <QSlider>

#include "clickablestyle.hpp"

class ClickableSlider : public QSlider
{
    Q_OBJECT

public:
    ClickableSlider(QWidget *parent = nullptr);
    ~ClickableSlider();

    bool isPressed() const;

signals:
    void sliderValueChanged(int value);

private slots:
    void onSliderPressed();
    void onSliderReleased();

private:
    void setup();

    bool m_pressed;
};

#endif // CLICKABLESLIDER_HPP
