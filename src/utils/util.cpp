#include "util.hpp"

/*
 * Converts a length in seconds into a time string.
 *
 * :param length: length in seconds
 * :return: time string
 */
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

/*
 * Loads the default cover and resizes it to a certain size.
 *
 * :param size: size, default -1
 * :return: default cover
 */
QPixmap Util::cover(int size)
{
    QPixmap pixmap(IMG_DEFAULT_COVER);
    if (size != -1)
        return Util::resize(pixmap, size);
    else
        return pixmap;
}

/*
 * Resizes a pixmap.
 *
 * :param pixmap: pixmap
 * :param size: size
 * :param fast: fast, default false
 * :return: scaled pixmap
 */
QPixmap Util::resize(const QPixmap &pixmap, int size, bool fast)
{
    return pixmap.scaled(size, size, Qt::KeepAspectRatio, fast ? Qt::FastTransformation : Qt::SmoothTransformation);
}

/*
 * Resizes an image.
 *
 * :param image: image
 * :param size: size
 * :param fast: fast, default false
 * :return: scaled image
 */
QImage Util::resize(const QImage &image, int size, bool fast)
{
    return image.scaled(size, size, Qt::KeepAspectRatio, fast ? Qt::FastTransformation : Qt::SmoothTransformation);
}

/*
 * Chunks a list into n evenly sized parts.
 *
 * :param list: list
 * :param n: n
 * :return: chunked list
 */
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
