#ifndef COLORUTIL_HPP
#define COLORUTIL_HPP

#include <QColor>
#include <QImage>
#include <QPixmap>
#include <QtMath>

class ColorUtil
{
public:
    static QColor darker(QColor color, qreal factor);
    static QColor averageColor(QImage image);
    static QColor dominantColor(QImage image);
    static QColor backgroundColor(QImage image, quint32 width = 50, quint32 height = 50);
    static QColor backgroundColor(QPixmap image, quint32 width = 50, quint32 height = 50);
};

#endif // COLORUTIL_HPP
