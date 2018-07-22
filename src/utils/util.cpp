#include "util.hpp"

QString Util::time(int seconds)
{
    QTime time(0, 0);
    time = time.addSecs(seconds);

    QString pattern;
    if (seconds < 600)
        pattern = "m:ss";
    else if (seconds < 3600)
        pattern = "mm:ss";
    else if (seconds < 36000)
        pattern = "h:mm:ss";
    else
        pattern = "hh:mm:ss";

    return time.toString(pattern);
}

QPixmap Util::cover(int size)
{
    return size == -1 ? QPixmap(IMG_DEFAULT_COVER) : Util::resize(QPixmap(IMG_DEFAULT_COVER), size);
}

QFont Util::font(double size)
{
    int id = QFontDatabase::addApplicationFont(FONT_LATO);
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);

    QFont font(family);
    font.setPointSizeF(size);
    font.setWeight(QFont::Weight::Medium);

    return font;
}

QPixmap Util::resize(const QPixmap &pixmap, int size, bool fast)
{
    return pixmap.scaled(size, size, Qt::KeepAspectRatio, fast ? Qt::FastTransformation : Qt::SmoothTransformation);
}

QImage Util::resize(const QImage &image, int size, bool fast)
{
    return image.scaled(size, size, Qt::KeepAspectRatio, fast ? Qt::FastTransformation : Qt::SmoothTransformation);
}

template <typename T>
QVector<QVector<T>> Util::chunk(const QVector<T> &vector, int n)
{
    n = qMin(qMax(1, n), vector.size());
    int quo = vector.size() / n;
    int rem = vector.size() % n;

    QVector<QVector<T>> result;
    for (int i = 0; i < n; ++i)
    {
        int l = i * quo + qMin(i, rem);
        int r = (i + 1) * quo + qMin(i + 1, rem);
        result << vector.mid(l, r - l);
    }
    return result;
}

template QVector<Files> Util::chunk<QString>(const Files &, int);
template QVector<Audios> Util::chunk<Audio *>(const Audios &, int);


