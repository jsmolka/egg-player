#ifndef COVER_HPP
#define COVER_HPP

#include <QColor>
#include <QPixmap>

#include "core/globals.hpp"

class Cover
{
public:
    Cover();
    explicit Cover(int id);

    static int defaultSize();
    static Cover defaultCover();
    static QPixmap loadFromFile(const QString &file);
    static QPixmap scale(const QPixmap &pixmap, int size, bool fast = false);

    void invalidate();
    bool isValid() const;

    void setId(int id);
    int id() const;

    QPixmap pixmap(int size = -1);
    QColor dominantColor();

private:
    static QPixmap coverify(const QPixmap &cover);
    static QPixmap loadFromCache(int id);
    static QColor rawDominantColor(const QImage &image);
    static QColor adjustDominantColor(const QColor &color);

    static constexpr int s_size{200};
    static constexpr int s_defaultId{1};
    static constexpr int s_dominantSize{30};

    int m_id;
};

#endif // COVER_HPP
