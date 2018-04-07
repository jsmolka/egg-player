#ifndef COLORUTIL_HPP
#define COLORUTIL_HPP

#include <QColor>
#include <QImage>
#include <QPixmap>
#include <QtMath>

class ColorUtil
{
public:
    static QColor darker(const QColor &color, qreal factor);
    static QColor averageColor(const QImage &image);
    static QColor dominantColor(const QImage &image);
    static QColor backgroundColor(const QImage &image, quint32 width = 50, quint32 height = 50);
    static QColor backgroundColor(const QPixmap &image, quint32 width = 50, quint32 height = 50);
};

#endif // COLORUTIL_HPP
