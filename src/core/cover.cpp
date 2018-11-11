#include "cover.hpp"

#include <QHash>
#include <QPainter>
#include <QVector>

#include <taglib/attachedpictureframe.h>
#include <taglib/id3v2frame.h>
#include <taglib/id3v2tag.h>
#include <taglib/mpegfile.h>

#include "core/cache.hpp"
#include "core/logger.hpp"
#include "core/utils.hpp"

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
    return 200;
}

Cover Cover::defaultCover()
{
    return Cover(1);
}

QPixmap Cover::loadFromFile(const QString &file)
{
    QPixmap cover;
    TagLib::MPEG::File mFile(Util::toWString(file));
    if (mFile.hasID3v2Tag())
    {
        const TagLib::ID3v2::Tag *tag = mFile.ID3v2Tag();
        const TagLib::ID3v2::FrameList frameList = tag->frameList("APIC");
        if (!frameList.isEmpty())
        {
            const TagLib::ID3v2::AttachedPictureFrame *frame = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(frameList.front());
            cover.loadFromData(reinterpret_cast<const uchar *>(frame->picture().data()), frame->picture().size());
        }
    }
    if (cover.isNull())
    {
        EGG_LOG("Cannot read cover %1", file);
        cover = defaultCover().pixmap();
    }
    return scale(coverify(cover), defaultSize());
}

QPixmap Cover::scale(const QPixmap &pixmap, int size, ScalePolicy policy)
{
    if (pixmap.height() == size && pixmap.width() == size)
        return pixmap;

    const Qt::TransformationMode mode =
        policy == ScalePolicy::Smooth
            ? Qt::SmoothTransformation
            : Qt::FastTransformation;

    return pixmap.scaled(size, size, Qt::KeepAspectRatio, mode);
}

bool Cover::isValid() const
{
    return m_id != 0;
}

void Cover::invalidate()
{
    m_id = 0;
}

QPixmap Cover::pixmap(int size)
{
    const int id = qMax(1, m_id);
    static QHash<int, QPixmap> cache;

    if (!cache.contains(id))
        cache.insert(id, Cache::loadCover(id));

    const QPixmap pixmap = cache.value(id);
    return size == 0 ? pixmap : scale(pixmap, size);
}

QColor Cover::color()
{
    const int id = qMax(1, m_id);
    static QHash<int, QColor> cache;

    if (!cache.contains(id))
    {
        const QColor raw = computeColor(scale(pixmap(), 30, ScalePolicy::Fast).toImage());
        cache.insert(id, adjustColor(raw).toRgb());
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

QColor Cover::computeColor(const QImage &image)
{
    static constexpr int range = 60;
    static constexpr int limit = 25;

    QVector<HsvRange> colorful(range);
    QVector<HsvRange> grey(range);

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
        const int x = h / (360 / range);

        if (qAbs(r - g) > limit
                || qAbs(g - b) > limit
                || qAbs(b - r) > limit)
        {
            isColorful = true;
            colorful[x].h += h;
            colorful[x].s += s;
            colorful[x].v += v;
            colorful[x].c++;
        }
        else if (!isColorful)
        {
            grey[x].h += h;
            grey[x].s += s;
            grey[x].v += v;
            grey[x].c++;
        }
    }
    return dominantColor(isColorful ? colorful : grey);
}

QColor Cover::dominantColor(const QVector<HsvRange> &ranges)
{
    int max = 0;
    HsvRange dominant = ranges.first();
    for (const HsvRange &range : ranges)
    {
        const int temp = range.h + 2 * range.s + 3 * range.v;
        if (temp > max)
        {
            dominant = range;
            max = temp;
        }
    }

    const float c = static_cast<float>(dominant.c);
    const int h = qRound(static_cast<float>(dominant.h) / c);
    const int s = qRound(static_cast<float>(dominant.s) / c);
    const int v = qRound(static_cast<float>(dominant.v) / c);

    return QColor::fromHsv(h, s, v);
}

QColor Cover::adjustColor(const QColor &color)
{
    const qreal h = color.hsvHueF();
    const qreal s = qMin(color.hsvSaturationF(), 0.8);
    const qreal v = qMin(color.valueF(), 0.36);

    return QColor::fromHsvF(h, s, v);
}
