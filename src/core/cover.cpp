#include "cache.hpp"
#include "cover.hpp"

Cover::Cover()
    : Cover(-1)
{

}

Cover::Cover(int id)
    : m_id(id)
{

}

Cover::~Cover()
{

}

int Cover::defaultSize()
{
    return s_size;
}

Cover Cover::defaultCover()
{
    return Cover(0);
}

QPixmap Cover::loadFromFile(const wchar_t *file)
{
    QPixmap cover = Tag(file).cover();
    if (cover.isNull())
        cover = loadFromCache(0);

    return scale(coverify(cover), s_size);
}

QPixmap Cover::scale(const QPixmap &pixmap, int size, bool fast)
{
    return pixmap.scaled(size, size, Qt::KeepAspectRatio, fast ? Qt::FastTransformation : Qt::SmoothTransformation);
}

void Cover::setId(int id)
{
    m_id = id;
}

int Cover::id() const
{
    return m_id;
}

QPixmap Cover::picture(int size)
{
    int id = qMax(0, m_id);
    static QHash<int, QPixmap> cache;
    if (!cache.contains(id))
        cache.insert(id, loadFromCache(id));

    QPixmap pixmap = cache.value(id);
    return size == -1 ? pixmap : scale(pixmap, size);
}

QColor Cover::dominantColor()
{
    int id = qMax(0, m_id);
    static QHash<int, QColor> cache;
    if (!cache.contains(id))
    {
        QColor raw = rawDominantColor(scale(picture(), 25, true).toImage());
        cache.insert(id, adjustDominantColor(raw).toRgb());
    }
    return cache.value(id);
}

QPixmap Cover::coverify(const QPixmap &cover)
{
    int height = cover.height();
    int width = cover.width();

    if (height != width)
    {
        int size = qMax(height, width);
        QPixmap square(size, size);
        square.fill(Qt::transparent);

        QPainter painter(&square);
        int x = (size - width) / 2;
        int y = (size - height) / 2;
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
        int mix()
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
        QColor rgb(pixels[i]);
        int r = rgb.red();
        int g = rgb.green();
        int b = rgb.blue();

        QColor hsv = rgb.toHsv();
        int h = qMax(0, hsv.hue());
        int s = hsv.saturation();
        int v = hsv.value();

        int index = h / (360 / range);

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

    auto dominantColor = [&range](std::array<HsvRange, range> hsvs) -> QColor
    {
        int idx = 0;
        int m = 0;
        for (int i = 0; i < range; ++i)
        {
            int t = hsvs[i].mix();
            if (t > m)
            {
                idx = i;
                m = t;
            }
        }

        float c = static_cast<float>(hsvs[idx].c);
        int h = static_cast<float>(hsvs[idx].h) / c;
        int s = static_cast<float>(hsvs[idx].s) / c;
        int v = static_cast<float>(hsvs[idx].v) / c;

        return QColor::fromHsv(h, s, v);
    };

    return dominantColor(isColorful ? colorful : grey);
}

QColor Cover::adjustDominantColor(const QColor &color)
{
    qreal hue = color.hsvHueF();
    qreal saturation = qMin(color.hsvSaturationF(), 0.8);
    qreal value = qMin(color.valueF(), 0.36);

    return QColor::fromHsvF(hue, saturation, value);
}
