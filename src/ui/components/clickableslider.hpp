#ifndef CLICKABLESLIDER_HPP
#define CLICKABLESLIDER_HPP

#include <QSlider>

#include "clickablesliderstyle.hpp"

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
    bool m_pressed;
};

#endif // CLICKABLESLIDER_HPP
