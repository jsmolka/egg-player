#ifndef UTILS_HPP
#define UTILS_HPP

#include <QColor>
#include <QDirIterator>
#include <QHash>
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
    static QPixmap resize(const QPixmap &pixmap, int size, bool fast = false);
    static QImage resize(const QImage &image, int size, bool fast = false);
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
    static QColor background(const QImage &image, int id = -1);
    static QColor background(const QPixmap &pixmap, int id = -1);

private:
    static QHash<int, QColor> _colorCache;
};

#endif // UTILS_HPP
