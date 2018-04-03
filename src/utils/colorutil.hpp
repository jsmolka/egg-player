#ifndef COLORUTIL_HPP
#define COLORUTIL_HPP

#include <QPixmap>

class ColorUtil
{
public:
    static QColor darken(QColor color, qreal factor);
    static QColor averageColor(QImage image);
    static QColor dominantColorByHue(QImage image);
    static QColor dominantColorBySaturation(QImage image);
    static QColor dominantColorByValue(QImage image);
    static QColor backgroundColor(QPixmap image);
    static QColor backgroundColor(QImage image);
};

#endif // COLORUTIL_HPP
