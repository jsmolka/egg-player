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
#include "types.hpp"

namespace Util
{
    extern QFont font(double size);

    template <typename T>
    extern QVector<QVector<T>> chunk(const QVector<T> &vector, int n);
}

#endif // UTIL_HPP
