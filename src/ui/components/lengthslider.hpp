#ifndef LENGTHSLIDER_HPP
#define LENGTHSLIDER_HPP

#include <QProxyStyle>
#include <QSlider>
#include <QStyle>
#include <QStyleOption>
#include <QPainter>

class LengthSliderStyle : public QProxyStyle
{
public:
    using QProxyStyle::QProxyStyle;

    int styleHint(QStyle::StyleHint hint, const QStyleOption* option = 0, const QWidget* widget = 0, QStyleHintReturn* returnData = 0) const
    {
        if (hint == QStyle::SH_Slider_AbsoluteSetButtons)
            return (Qt::LeftButton | Qt::MidButton | Qt::RightButton);

        return QProxyStyle::styleHint(hint, option, widget, returnData);
    }
};

class LengthSlider : public QSlider
{
    Q_OBJECT

public:
    LengthSlider(QWidget *parent = nullptr);
    ~LengthSlider();

    bool isPressed() const;

signals:
    void positionChanged(int position);

private slots:
    void onSliderPressed();
    void onSliderReleased();
    void onSliderMoved(int value);

private:
    bool m_pressed;
    int m_value;
};

#endif // LENGTHSLIDER_HPP
