#include "cover.hpp"

#include <array>

#include <QHash>
#include <QPainter>

#include "cache.hpp"
#include "logger.hpp"
#include "tag.hpp"

Cover::Cover()
    : Cover(0)
{

}

Cover::Cover(int id)
    : m_id(id)
{

}

int Cover::defaultSize()
{
    return s_size;
}

Cover Cover::defaultCover()
{
    return Cover(s_defaultId);
}

QPixmap Cover::loadFromFile(const File &file)
{
    QPixmap cover = Tag(file).readCover();
    if (cover.isNull())
        cover = loadFromCache(s_defaultId);

    return scale(coverify(cover), s_size);
}

QPixmap Cover::scale(const QPixmap &pixmap, int size, bool fast)
{
    return pixmap.scaled(size, size, Qt::KeepAspectRatio, fast ? Qt::FastTransformation : Qt::SmoothTransformation);
}

void Cover::invalidate()
{
    m_id = 0;
}

bool Cover::isValid() const
{
    return m_id > 0;
}

void Cover::setId(int id)
{
    m_id = id;
}

int Cover::id() const
{
    return m_id;
}

QPixmap Cover::pixmap(int size)
{
    const int id = qMax(1, m_id);
    static QHash<int, QPixmap> cache;
    if (!cache.contains(id))
        cache.insert(id, loadFromCache(id));

    const QPixmap pixmap = cache.value(id);
    return size == -1 ? pixmap : scale(pixmap, size);
}

QColor Cover::dominantColor()
{
    const int id = qMax(1, m_id);
    static QHash<int, QColor> cache;
    if (!cache.contains(id))
    {
        const QColor raw = rawDominantColor(scale(pixmap(), s_dominantSize, true).toImage());
        cache.insert(id, adjustDominantColor(raw).toRgb());
    }
    return cache.value(id);
}

QPixmap Cover::coverify(const QPixmap &cover)
{
    const int height = cover.height();
    const int width = cover.width();

    if (height != width)
    {
        const int size = qMax(height, width);
        QPixmap square(size, size);
        square.fill(Qt::transparent);

        QPainter painter(&square);
        const int x = (size - width) / 2;
        const int y = (size - height) / 2;
        painter.drawPixmap(x, y, cover);
        return square;
    }
    return cover;
}

QPixmap Cover::loadFromCache(int id)
{
    return Cache().coverById(id);
}

QColor Cover::rawDominantColor(const QImage &image)
{
    constexpr int range = 60;
    constexpr int limit = 25;

    struct HsvRange
    {
        int mix() const
        {
            return h + 2 * s + 3 * v;
        }

        int h;
        int s;
        int v;
        int c;
    };

    std::array<HsvRange, range> colorful = {};
    std::array<HsvRange, range> grey = {};

    bool isColorful = false;
    QRgb *pixels = (QRgb *)image.bits();
    for (int i = 0; i < image.height() * image.width(); ++i)
    {
        const QColor rgb(pixels[i]);
        const int r = rgb.red();
        const int g = rgb.green();
        const int b = rgb.blue();

        const QColor hsv = rgb.toHsv();
        const int h = qMax(0, hsv.hue());
        const int s = hsv.saturation();
        const int v = hsv.value();

        const int index = h / (360 / range);

        if (qAbs(r - g) > limit || qAbs(g - b) > limit || qAbs(b - r) > limit)
        {
            isColorful = true;
            colorful[index].h += h;
            colorful[index].s += s;
            colorful[index].v += v;
            ++colorful[index].c;
        }
        else if (!isColorful)
        {
            grey[index].h += h;
            grey[index].s += s;
            grey[index].v += v;
            ++grey[index].c;
        }
    }

    const static auto dominantColor = [](std::array<HsvRange, range> hsvs) -> QColor
    {
        int max = 0;
        HsvRange most = hsvs[0];
        for (const HsvRange &hsv : hsvs)
        {
            const int temp = hsv.mix();
            if (temp > max)
            {
                most = hsv;
                max = temp;
            }
        }

        const float c = static_cast<float>(most.c);
        const int h = static_cast<float>(most.h) / c;
        const int s = static_cast<float>(most.s) / c;
        const int v = static_cast<float>(most.v) / c;

        return QColor::fromHsv(h, s, v);
    };

    return dominantColor(isColorful ? colorful : grey);
}

QColor Cover::adjustDominantColor(const QColor &color)
{
    const qreal hue = color.hsvHueF();
    const qreal saturation = qMin(color.hsvSaturationF(), 0.8);
    const qreal value = qMin(color.valueF(), 0.36);

    return QColor::fromHsvF(hue, saturation, value);
}
