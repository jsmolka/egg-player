#include "colorutil.hpp"

QColor ColorUtil::darken(QColor color, qreal factor)
{
    qreal red = (qreal) color.red() * factor;
    qreal green = (qreal) color.green() * factor;
    qreal blue = (qreal) color.blue() * factor;

    return QColor(red, green, blue);
}

QColor ColorUtil::averageColor(QImage image)
{
    QRgb *pixels = (QRgb *) image.bits();
    quint32 pixelCount = image.height() * image.width();

    quint32 red = 0;
    quint32 green = 0;
    quint32 blue = 0;

    for (quint32 i = 0; i < pixelCount; i++)
    {
        QColor pixel = QColor(pixels[i]);
        red += pixel.red();
        green += pixel.green();
        blue += pixel.blue();
    }

    red = red / pixelCount;
    green = green / pixelCount;
    blue = blue / pixelCount;

    return QColor(red, green, blue);
}

QColor ColorUtil::backgroundColor(QPixmap image)
{
    return backgroundColor(image.toImage());
}

QColor ColorUtil::backgroundColor(QImage image)
{
    return ColorUtil::darken(averageColor(image));
}
