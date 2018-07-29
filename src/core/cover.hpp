#ifndef COVER_HPP
#define COVER_HPP

#include <QColor>
#include <QHash>
#include <QPainter>
#include <QPixmap>

#include "logger.hpp"
#include "tag.hpp"

class Cover
{
public:
    Cover();
    Cover(int id);
    ~Cover();

    static int defaultSize();
    static Cover defaultCover();
    static QPixmap loadFromFile(const wchar_t *file);

    void setId(int id);
    int id() const;

    QPixmap picture(int size = -1);
    QColor dominantColor();

private:
    static QPixmap coverify(const QPixmap &cover);
    static QPixmap resize(const QPixmap &pixmap, int size, bool fast);
    static QPixmap loadFromCache(int id);

    QColor rawDominantColor(const QImage &image);
    QColor adjustDominantColor(const QColor &color);

    static constexpr int _size = 200;
    static QHash<int, QPixmap> _covers;
    static QHash<int, QColor> _colors;

    int m_id;
};

#endif // COVER_HPP
