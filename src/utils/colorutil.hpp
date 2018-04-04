#ifndef COLORUTIL_HPP
#define COLORUTIL_HPP

#include <QColor>
#include <QImage>
#include <QPixmap>

class ColorUtil
{
public:
    enum Hsv {Hue, Saturation, Value};

    static QColor darken(QColor color, qreal factor);
    static QColor averageColor(QImage image);
    static QColor dominantColor(QImage image, Hsv portion);
    static QColor backgroundColor(QImage image, quint32 width = 50, quint32 height = 50);
    static QColor backgroundColor(QPixmap image, quint32 width = 50, quint32 height = 50);
};

#endif // COLORUTIL_HPP
