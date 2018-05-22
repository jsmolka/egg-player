#ifndef UTILS_HPP
#define UTILS_HPP

#include <array>

#include <QColor>
#include <QDirIterator>
#include <QImage>
#include <QPixmap>
#include <QTextStream>
#include <QTime>

#include "logger.hpp"
#include "types.hpp"

class Util
{
public:
    static QString time(int length);
    static QPixmap cover(int size = -1);
    static QPixmap resize(const QPixmap &pixmap, int size);
    static QImage resize(const QImage &image, int size);
    static QVector<StringList> chunk(const StringList &list, int n);
};

class FileUtil
{
public:
    static QString read(const QString &file);
    static bool exists(const QString &path);
    static QString fileName(const QString &file);
    static StringList glob(const QString &path, const QString &suffix);
};

class ColorUtil
{
public:
    static QColor dominant(const QImage &image);
    static QColor background(const QImage &image, quint32 size = 25);
    static QColor background(const QPixmap &image, quint32 size = 25);
};

#endif // UTILS_HPP
