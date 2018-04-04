#ifndef COLORUTIL_HPP
#define COLORUTIL_HPP

#include <QPixmap>
#include <QtMath>

class ColorUtil
{
public:
    enum Hsv {Hue, Saturation, Value};

    static QColor darken(QColor color, qreal factor);
    static QColor averageColor(QImage image);
    static QColor dominantColorHsv(QImage image, Hsv part);
    static QColor backgroundColor(QPixmap image);
    static QColor backgroundColor(QImage image);
};

#endif // COLORUTIL_HPP
