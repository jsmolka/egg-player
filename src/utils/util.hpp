#ifndef UTIL_HPP
#define UTIL_HPP

#include <QImage>
#include <QPixmap>
#include <QTime>

#include "constants.hpp"
#include "types.hpp"

namespace Util
{
    extern QString time(int length);
    extern QPixmap defaultCover(int size = -1);
    extern QPixmap resize(const QPixmap &pixmap, int size, bool fast = false);
    extern QImage resize(const QImage &image, int size, bool fast = false);
    extern QVector<StringList> chunk(const StringList &list, int n);
}

#endif // UTIL_HPP
