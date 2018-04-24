#ifndef LENGTHSLIDER_HPP
#define LENGTHSLIDER_HPP

#include <QPainter>
#include <QProxyStyle>
#include <QSlider>
#include <QStyle>
#include <QStyleOption>

class LengthSliderStyle : public QProxyStyle
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

private:
    bool m_pressed;
};

#endif // LENGTHSLIDER_HPP
