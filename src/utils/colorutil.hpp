#ifndef COLORUTIL_HPP
#define COLORUTIL_HPP

#include <QPixmap>

class ColorUtil
{
public:
    static QColor darken(QColor color, qreal factor);
    static QColor averageColor(QImage image);
    static QColor dominantColor(QImage image);
    static QColor backgroundColor(QPixmap image);
    static QColor backgroundColor(QImage image);
};

#endif // COLORUTIL_HPP
