#ifndef UTILS_HPP
#define UTILS_HPP

#include <array>

#include <QColor>
#include <QDir>
#include <QFont>
#include <QFontDatabase>
#include <QImage>
#include <QPixmap>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QTime>

#include "logger.hpp"

class Utils
{
public:
    // General
    static QString timeString(int length);
    static QPixmap defaultCover(int size = -1);
    static QPixmap resize(const QPixmap &pixmap, int size);
    static QImage resize(const QImage &image, int size);
    static QFont loadFont();

    // File
    static QString read(const QString &path);
    static bool exists(const QString &path);
    static QDir dir(const QString &path);
    static QStringList glob(const QString &path, const QString &pattern, bool recursive = true);
    static QString fileName(const QString &file);
    static void checkResources();
    static QString documents();

    // Color
    static QColor dominantColor(const QImage &image);
    static QColor backgroundColor(const QImage &image, quint32 size = 25);
    static QColor backgroundColor(const QPixmap &image, quint32 size = 25);
};

#endif // UTILS_HPP
