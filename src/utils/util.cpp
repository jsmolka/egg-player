#include "util.hpp"

QString Util::time(int length)
{
    int seconds = length % 60;
    int minutes = length / 60 % 60;
    int hours = length / 3600 % 60;

    QString format;
    if (hours > 9)
        format = "hh:mm:ss";
    else if (hours > 0)
        format = "h:mm:ss";
    else if (minutes > 9)
        format = "mm:ss";
    else
        format = "m:ss";

    return QTime(hours, minutes, seconds).toString(format);
}

QPixmap Util::defaultCover(int size)
{
    QPixmap pixmap(IMG_DEFAULT_COVER);
    if (size != -1)
        return Util::resize(pixmap, size);
    else
        return pixmap;
}

QPixmap Util::resize(const QPixmap &pixmap, int size, bool fast)
{
    if (pixmap.height() == size && pixmap.width() == size)
        return pixmap;
    else
        return pixmap.scaled(size, size, Qt::KeepAspectRatio, fast ? Qt::FastTransformation : Qt::SmoothTransformation);
}

QImage Util::resize(const QImage &image, int size, bool fast)
{
    if (image.height() == size && image.width() == size)
        return image;
    else
        return image.scaled(size, size, Qt::KeepAspectRatio, fast ? Qt::FastTransformation : Qt::SmoothTransformation);
}

QVector<StringList> Util::chunk(const StringList &list, int n)
{
    n = qMin(qMax(1, n), list.size());
    int quo = list.size() / n;
    int rem = list.size() % n;

    QVector<StringList> result;
    for (int i = 0; i < n; i++)
    {
        int l = i * quo + qMin(i, rem);
        int r = (i + 1) * quo + qMin(i + 1, rem);
        result << list.mid(l, r - l);
    }
    return result;
}
