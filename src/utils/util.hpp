#ifndef UTIL_HPP
#define UTIL_HPP

#include <QImage>
#include <QPixmap>
#include <QTime>

#include "constants.hpp"
#include "types.hpp"

class Util
{
public:
    static QString time(int length);
    static QPixmap cover(int size = -1);
    static QPixmap resize(const QPixmap &pixmap, int size, bool fast = false);
    static QImage resize(const QImage &image, int size, bool fast = false);
    static QVector<StringList> chunk(const StringList &list, int n);
};

#endif // UTIL_HPP
