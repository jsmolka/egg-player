#ifndef UTILS_HPP
#define UTILS_HPP

#include <array>

#include <QColor>
#include <QDir>
#include <QImage>
#include <QPixmap>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QTime>

#include "logger.hpp"

/*
 * The Utils class contains utility functions which get
 * used a lot and do not belong into the classes. It
 * consists of general, file and color related functions.
 */
class Utils
{
public:
    // General
    static QString timeString(int length);

    // File
    static QString read(const QString &path);
    static bool exists(const QString &path);
    static QDir dir(const QString &path);
    static QStringList glob(const QString &path, const QString &pattern, bool recursive = true);
    static QString fileName(const QString &file);

    // Color
    static QColor darker(const QColor &color, qreal factor);
    static QColor averageColor(const QImage &image);
    static QColor dominantColor(const QImage &image);
    static QColor backgroundColor(const QImage &image, quint32 size = 50);
    static QColor backgroundColor(const QPixmap &image, quint32 size = 50);
};

#endif // UTILS_HPP
