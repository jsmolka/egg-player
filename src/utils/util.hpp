#ifndef UTIL_HPP
#define UTIL_HPP

#include <QFont>
#include <QFontDatabase>
#include <QImage>
#include <QPixmap>
#include <QTime>

#include "audio.hpp"
#include "constants.hpp"
#include "config.hpp"

namespace Util
{
    extern QString time(int seconds);
    extern QPixmap cover(int size = -1);
    extern QFont font(double size);

    extern QPixmap resize(const QPixmap &pixmap, int size, bool fast = false);
    extern QImage resize(const QImage &image, int size, bool fast = false);

    template <typename T>
    extern QVector<QVector<T>> chunk(const QVector<T> &vector, int n);
}

#endif // UTIL_HPP
