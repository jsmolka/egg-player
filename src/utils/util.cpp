#include "util.hpp"

QFont Util::font(double size)
{
    int id = QFontDatabase::addApplicationFont(FONT_LATO);
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);

    QFont font(family);
    font.setPointSizeF(size);
    font.setWeight(QFont::Weight::Medium);

    return font;
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


