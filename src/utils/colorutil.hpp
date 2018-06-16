#ifndef COLORUTIL_HPP
#define COLORUTIL_HPP

#include <QColor>
#include <QHash>
#include <QImage>
#include <QPixmap>

#include "util.hpp"

namespace ColorUtil
{
    extern QColor dominant(const QImage &image);
    extern QColor background(const QImage &image, int id = -1);
    extern QColor background(const QPixmap &pixmap, int id = -1);
}

namespace ColorUtilPrivate
{
    extern QHash<int, QColor> colors;
}

#endif // COLORUTIL_HPP
