#ifndef COLORUTIL_HPP
#define COLORUTIL_HPP

#include <QImage>
#include <QPixmap>

class ColorUtil
{
public:
    static QColor darken(QColor color, qreal factor = 0.6);
    static QColor averageColor(QImage image);
    static QColor backgroundColor(QPixmap image);
    static QColor backgroundColor(QImage image);
};

#endif // COLORUTIL_HPP
