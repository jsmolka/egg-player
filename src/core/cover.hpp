#ifndef COVER_HPP
#define COVER_HPP

#include <QColor>
#include <QPixmap>

#include "core/globals.hpp"

class Cover
{
public:
    enum ScalePolicy {Fast, Smooth};

    explicit Cover();
    explicit Cover(int id);

    static int defaultSize();
    static Cover defaultCover();
    static QPixmap loadFromFile(const QString &file);
    static QPixmap scale(const QPixmap &pixmap, int size, ScalePolicy policy = ScalePolicy::Smooth);

    EGG_PPROP(int, id, setId, id)

    bool isValid() const;
    void invalidate();

    QPixmap pixmap(int size = -1);
    QColor color();

private:
    struct HsvRange
    {
        int h;
        int s;
        int v;
        int c;
    };
    static QPixmap loadFromCache(int id);
    static QPixmap coverify(const QPixmap &cover);
    static QColor computeColor(const QImage &image);
    static QColor dominantColor(const QVector<HsvRange> &ranges);
    static QColor adjustColor(const QColor &color);
};

#endif // COVER_HPP
