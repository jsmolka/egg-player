#ifndef CLICKABLESLIDER_HPP
#define CLICKABLESLIDER_HPP

#include <QPainter>
#include <QProxyStyle>
#include <QSlider>
#include <QStyle>
#include <QStyleOption>

class ClickableSliderStyle : public QProxyStyle
{
public:
    using QProxyStyle::QProxyStyle;

    int styleHint(QStyle::StyleHint hint, const QStyleOption* option = nullptr, const QWidget* widget = nullptr, QStyleHintReturn* returnData = nullptr) const
    {
        if (hint == QStyle::SH_Slider_AbsoluteSetButtons)
            return Qt::LeftButton;

        return QProxyStyle::styleHint(hint, option, widget, returnData);
    }
};

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
