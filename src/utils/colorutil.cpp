#include "colorutil.hpp"

QColor ColorUtil::darker(QColor color, qreal factor)
{
    qreal r = (qreal) color.red() * (1 - factor);
    qreal g = (qreal) color.green() * (1 - factor);
    qreal b = (qreal) color.blue() * (1 - factor);
    return QColor(r, g, b);
}

QColor ColorUtil::averageColor(const QImage &image)
{
    quint32 red = 0;
    quint32 green = 0;
    quint32 blue = 0;

    // Iterate over every pixel
    QRgb *pixels = (QRgb *) image.bits();
    quint32 pixelCount = image.height() * image.width();
    for (quint32 i = 0; i < pixelCount; i++)
    {
        QColor pixel = QColor(pixels[i]);

        // Add current rgb value to total value
        red += pixel.red();
        green += pixel.green();
        blue += pixel.blue();
    }

    // Divide total value by pixel count
    red = red / pixelCount;
    green = green / pixelCount;
    blue = blue / pixelCount;
    return QColor(red, green, blue);
}

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

    // Iterate over every pixel
    QRgb *pixels = (QRgb *) image.bits();
    quint32 pixelCount = image.height() * image.width();
    for (quint32 i = 0; i < pixelCount; i++)
    {
        // Get rgb values
        QColor rgb = QColor(pixels[i]);
        quint32 red = rgb.red();
        quint32 green = rgb.green();
        quint32 blue = rgb.blue();

        // Get hsv values
        QColor hsv = rgb.toHsv();
        quint32 hue = hsv.hsvHue() == -1 ? 0 : rgb.hsvHue();
        quint32 saturation = hsv.hsvSaturation();
        quint32 value = hsv.value();

        quint32 index = hue / (360 / RANGE);

        // Check if color is 'colorful' or a grey scale
        if (qAbs(red - green) < 25 && qAbs(green - blue) < 25)
        {
            // Current color is a grey scale
            gCounts[index]++;
            gHues[index] += hue;
            gSaturations[index] += saturation;
            gValues[index] += value;
        }
        else
        {
            // Current color is 'colorful'
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
        // Return dominant 'colorful' color
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
        // Return dominant grey scale
        quint32 hue = gHues[index] / gCounts[index];
        quint32 saturation = gSaturations[index] / gCounts[index];
        quint32 value = gValues[index] / gCounts[index];
        return QColor::fromHsv(hue, saturation, value);
    }
}

QColor ColorUtil::backgroundColor(const QImage &image, quint32 width, quint32 height)
{
    // Get dominant color of scaled picture
    QColor color = dominantColor(image.scaled(width, height));

    // Darken the color to prevent too bright colors
    return darker(color.toRgb(), 0.4);
}

QColor ColorUtil::backgroundColor(const QPixmap &image, quint32 width, quint32 height)
{
    return backgroundColor(image.toImage(), height, width);
}
