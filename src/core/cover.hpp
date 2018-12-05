#ifndef COVER_HPP
#define COVER_HPP

#include <QColor>
#include <QPixmap>

#include "core/macros.hpp"

class Cover
{
public:
    enum ScalePolicy {Fast, Smooth};

    Cover();
    explicit Cover(int id);

    static int defaultSize();
    static Cover defaultCover();
    static QPixmap loadFromFile(const QString &file);
    static QPixmap scale(const QPixmap &pixmap, int size, ScalePolicy policy = ScalePolicy::Smooth);

    EGG_P_PROP(int, id, setId, id)

    bool isValid() const;
    void invalidate();

    QPixmap pixmap(int size = 0) const;
    QColor color() const;

private:
    struct HsvRange
    {
        int h;
        int s;
        int v;
        int c;
    };
    static QPixmap readFromFile(const QString &file);
    static QPixmap coverify(const QPixmap &cover);
    static QColor computeColor(const QImage &image);
    static QColor dominantColor(const QVector<HsvRange> &ranges);
    static QColor adjustColor(const QColor &color);
};

#endif // COVER_HPP
