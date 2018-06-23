#ifndef COLORUTIL_HPP
#define COLORUTIL_HPP

#include <QColor>
#include <QImage>
#include <QPixmap>

#include "util.hpp"

namespace ColorUtil
{
    extern QColor dominant(const QImage &image);
    extern QColor background(const QImage &image);
    extern QColor background(const QPixmap &pixmap);
}

#endif // COLORUTIL_HPP
