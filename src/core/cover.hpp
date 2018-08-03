#ifndef COVER_HPP
#define COVER_HPP

#include <array>

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
    static QPixmap scale(const QPixmap &pixmap, int size, bool fast = false);

    bool isValid() const;

    void setId(int id);
    int id() const;

    QPixmap picture(int size = -1);
    QColor dominantColor();

private:
    static QPixmap coverify(const QPixmap &cover);
    static QPixmap loadFromCache(int id);
    static QColor rawDominantColor(const QImage &image);
    static QColor adjustDominantColor(const QColor &color);

    static constexpr int s_size = 200;

    int m_id;
};

#endif // COVER_HPP
