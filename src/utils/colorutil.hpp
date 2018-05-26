#ifndef COLORUTIL_HPP
#define COLORUTIL_HPP

#include <QColor>
#include <QHash>
#include <QImage>
#include <QPixmap>

#include "util.hpp"

class ColorUtil
{
public:
    static QColor dominant(const QImage &image);
    static QColor background(const QImage &image, int id = -1);
    static QColor background(const QPixmap &pixmap, int id = -1);

private:
    static QHash<int, QColor> _colorCache;
};

#endif // COLORUTIL_HPP
