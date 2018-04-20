#include "colorutil.hpp"

/*
 * Darkens a rgb cover.
 *
 * :param color: color to darken
 * :param factor: factor to darken with (1 - factor)
 * :return: darkened color
 */
QColor ColorUtil::darker(const QColor &color, qreal factor)
{
    qreal r = (qreal) color.red() * (1 - factor);
    qreal g = (qreal) color.green() * (1 - factor);
    qreal b = (qreal) color.blue() * (1 - factor);

    return QColor(r, g, b);
}

/*
 * Calculates average color by iterating
 * over every pixel, adding them and then
 * dividing by the pixel count.
 *
 * :param image: image to process
 * :return: average color
 */
QColor ColorUtil::averageColor(const QImage &image)
{
    quint32 red = 0;
    quint32 green = 0;
    quint32 blue = 0;

    QRgb *pixels = (QRgb *) image.bits();
    quint32 pixelCount = image.height() * image.width();
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

/*
 * Calculates dominent color of an image. The algorithm
 * iterates over every pixel, converts them into the
 * HSV color space and creates a mapped heuristic out of
 * them.
 * There are always two heuristics. One holds all
 * 'colorful' colors and the other one holds grey scale
 * colors. If there are no 'colorful' colors the grey scale
 * gets chosen.
 *
 * :param image: image to process
 * :return: dominant color
 */
QColor ColorUtil::dominantColor(const QImage &image)
{
    // Map 360 hues to RANGE
    const quint32 RANGE = 18;

    // Initialize arrays for 'colorful' colors
    std::array<quint32, RANGE> cCounts;
    std::array<quint32, RANGE> cHues;
    std::array<quint32, RANGE> cSaturations;
    std::array<quint32, RANGE> cValues;

    cCounts.fill(0);
    cHues.fill(0);
    cSaturations.fill(0);
    cValues.fill(0);

    // Initialize arrays for grey scale colors
    std::array<quint32, RANGE> gCounts;
    std::array<quint32, RANGE> gHues;
    std::array<quint32, RANGE> gSaturations;
    std::array<quint32, RANGE> gValues;

    gCounts.fill(0);
    gHues.fill(0);
    gSaturations.fill(0);
    gValues.fill(0);

    QRgb *pixels = (QRgb *) image.bits();
    quint32 pixelCount = image.height() * image.width();
    for (quint32 i = 0; i < pixelCount; i++)
    {
        QColor rgb = QColor(pixels[i]);
        quint32 red = rgb.red();
        quint32 green = rgb.green();
        quint32 blue = rgb.blue();

        QColor hsv = rgb.toHsv();
        quint32 hue = hsv.hsvHue() == -1 ? 0 : rgb.hsvHue();
        quint32 saturation = hsv.hsvSaturation();
        quint32 value = hsv.value();

        quint32 index = hue / (360 / RANGE);

        // Check if color is 'colorful' or a grey scale
        if (qAbs(red - green) < 25 && qAbs(green - blue) < 25 && qAbs(red - blue) < 25)
        {
            gCounts[index]++;
            gHues[index] += hue;
            gSaturations[index] += saturation;
            gValues[index] += value;
        }
        else
        {
            cCounts[index]++;
            cHues[index] += hue;
            cSaturations[index] += saturation;
            cValues[index] += value;
        }
    }

    // Try to get the dominant 'colorful' color
    quint32 index = 0;
    quint32 max = 0;
    for (quint32 i = 0; i < RANGE; i++)
    {
        quint32 temp = cHues[i] + 2 * cSaturations[i] + 3 * cValues[i];
        if (temp > max)
        {
            index = i;
            max = temp;
        }
    }

    if (cCounts[index] != 0)
    {
        quint32 hue = cHues[index] / cCounts[index];
        quint32 saturation = cSaturations[index] / cCounts[index];
        quint32 value = cValues[index] / cCounts[index];

        return QColor::fromHsv(hue, saturation, value);
    }
    else
    {
        // Choose a grey scale if there is no 'colorful' color
        index = 0;
        max = 0;
        for (quint32 i = 0; i < RANGE; i++)
        {
            quint32 temp = gHues[i] + 2 * gSaturations[i] + 3 * gValues[i];
            if (temp > max)
            {
                index = i;
                max = temp;
            }
        }

        quint32 hue = gHues[index] / gCounts[index];
        quint32 saturation = gSaturations[index] / gCounts[index];
        quint32 value = gValues[index] / gCounts[index];

        return QColor::fromHsv(hue, saturation, value);
    }
}

/*
 * Calculates background color by darkening
 * the dominant color to prevent too bright
 * colors.
 *
 * :param image: image to process
 * :param size: image size to scale to
 * :return: background color
 */
QColor ColorUtil::backgroundColor(const QImage &image, quint32 size)
{
    QColor color = dominantColor(image.scaled(size, size));

    return darker(color.toRgb(), 0.4);
}

/*
 * Overloaded function.
 *
 * :param image: image to process
 * :param size: image size to scale to
 * :return: background color
 */
QColor ColorUtil::backgroundColor(const QPixmap &image, quint32 size)
{
    return backgroundColor(image.toImage(), size);
}
