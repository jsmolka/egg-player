#include "colorutil.hpp"

QColor ColorUtil::darken(QColor color, qreal factor)
{
    qreal r = (qreal) color.red() * (1 - factor);
    qreal g = (qreal) color.green() * (1 - factor);
    qreal b = (qreal) color.blue() * (1 - factor);

    return QColor(r, g, b);
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

QColor ColorUtil::dominantColorByHue(QImage image)
{
    const quint32 RANGE = 360;

    QRgb *pixels = (QRgb *) image.bits();
    quint32 pixelCount = image.height() * image.width();

    std::array<quint32, RANGE> hues;
    std::array<quint32, RANGE> saturations;
    std::array<quint32, RANGE> values;

    hues.fill(0);
    saturations.fill(0);
    values.fill(0);

    for (quint32 i = 0; i < pixelCount; i++)
    {
        QColor pixel = QColor(pixels[i]).toHsv();

        qint32 hue = pixel.hsvHue();
        quint32 saturation = pixel.hsvSaturation();
        quint32 value = pixel.value();

        if (hue == -1)
            hue = 0;

        hues[hue]++;
        saturations[hue] += saturation;
        values[hue] += value;
    }

    quint32 hue = 0;
    quint32 satuation;
    quint32 value;

    quint32 hueCount = hues[0];
    for (quint32 i = 1; i < RANGE; i++)
    {
        if (hues[i] > hueCount)
        {
            hue = i;
            hueCount = hues[i];
        }
    }

    satuation = saturations[hue] / hueCount;
    value = values[hue] / hueCount;

    return QColor::fromHsv(hue, satuation, value).toRgb();
}

QColor ColorUtil::dominantColorBySaturation(QImage image)
{
    const quint32 RANGE = 360;

    QRgb *pixels = (QRgb *) image.bits();
    quint32 pixelCount = image.height() * image.width();

    std::array<quint32, RANGE> hues;
    std::array<quint32, RANGE> saturations;
    std::array<quint32, RANGE> values;

    hues.fill(0);
    saturations.fill(0);
    values.fill(0);

    for (quint32 i = 0; i < pixelCount; i++)
    {
        QColor pixel = QColor(pixels[i]).toHsv();

        qint32 hue = pixel.hsvHue();
        quint32 saturation = pixel.hsvSaturation();
        quint32 value = pixel.value();

        if (hue == -1)
            hue = 0;

        hues[hue]++;
        saturations[hue] += saturation;
        values[hue] += value;
    }

    quint32 hue = 0;
    quint32 satuation;
    quint32 value;

    quint32 maxSaturation = saturations[0];
    for (quint32 i = 1; i < RANGE; i++)
    {
        if (saturations[i] > maxSaturation)
        {
            hue = i;
            maxSaturation = saturations[i];
        }
    }

    satuation = saturations[hue] / hues[hue];
    value = values[hue] / hues[hue];

    return QColor::fromHsv(hue, satuation, value).toRgb();
}

QColor ColorUtil::dominantColorByValue(QImage image)
{
    const quint32 RANGE = 360;

    QRgb *pixels = (QRgb *) image.bits();
    quint32 pixelCount = image.height() * image.width();

    std::array<quint32, RANGE> hues;
    std::array<quint32, RANGE> saturations;
    std::array<quint32, RANGE> values;

    hues.fill(0);
    saturations.fill(0);
    values.fill(0);

    for (quint32 i = 0; i < pixelCount; i++)
    {
        QColor pixel = QColor(pixels[i]).toHsv();

        qint32 hue = pixel.hsvHue();
        quint32 saturation = pixel.hsvSaturation();
        quint32 value = pixel.value();

        if (hue == -1)
            hue = 0;

        hues[hue]++;
        saturations[hue] += saturation;
        values[hue] += value;
    }

    quint32 hue = 0;
    quint32 satuation;
    quint32 value;

    quint32 maxValue = values[0];
    for (quint32 i = 1; i < RANGE; i++)
    {
        if (values[i] > maxValue)
        {
            hue = i;
            maxValue = values[i];
        }
    }

    satuation = saturations[hue] / hues[hue];
    value = values[hue] / hues[hue];

    return QColor::fromHsv(hue, satuation, value).toRgb();
}

QColor ColorUtil::backgroundColor(QPixmap image)
{
    return backgroundColor(image.toImage());
}

QColor ColorUtil::backgroundColor(QImage image)
{
    return darken(dominantColorByValue(image), 0.6);
}
