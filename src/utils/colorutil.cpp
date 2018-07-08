#include "colorutil.hpp"

QColor ColorUtil::dominant(const QImage &image)
{
    const quint32 RANGE = 60;

    quint32 cCounts[RANGE] = {};
    quint32 cHues[RANGE] = {};
    quint32 cSaturations[RANGE] = {};
    quint32 cValues[RANGE] = {};

    quint32 gCounts[RANGE] = {};
    quint32 gHues[RANGE] = {};
    quint32 gSaturations[RANGE] = {};
    quint32 gValues[RANGE] = {};

    QRgb *pixels = (QRgb *)image.bits();
    quint32 pixelCount = image.height() * image.width();
    for (quint32 i = 0; i < pixelCount; i++)
    {
        QColor rgb = QColor(pixels[i]);
        qint32 red = rgb.red();
        qint32 green = rgb.green();
        qint32 blue = rgb.blue();

        QColor hsv = rgb.toHsv();
        qint32 hue = qMax(0, hsv.hsvHue());
        qint32 saturation = hsv.hsvSaturation();
        qint32 value = hsv.value();

        quint32 index = hue / (360 / RANGE);

        const qint32 limit = 25;
        if (qAbs(red - green) < limit && qAbs(green - blue) < limit && qAbs(red - blue) < limit)
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

QColor ColorUtil::background(const QImage &image)
{
    QColor color = dominant(Util::resize(image, 25, true));
    qreal hue = color.hsvHueF();
    qreal saturation = qMin(color.hsvSaturationF(), 0.8);
    qreal value = qMin(color.valueF(), 0.36);

    return QColor::fromHsvF(hue, saturation, value);
}

QColor ColorUtil::background(const QPixmap &pixmap)
{
    return background(pixmap.toImage());
}
