#include "utils.hpp"

/*
 * Converts a length in seconds into a time
 * string. If automatically uses the correct
 * format depending on the length.
 *
 * :param length: length in seconds
 * :return: time string
 */
QString Utils::timeString(int length)
{
    int seconds = length % 60;
    int minutes = (length / 60) % 60;
    int hours = (length / 3600) % 60;

    QString pattern = "m:ss";
    if (minutes > 9)
        pattern = "mm:ss";
    if (hours > 0)
        pattern = "h:mm:ss";
    if (hours > 9)
        pattern = "hh:mm:ss";

    return QTime(hours, minutes, seconds).toString(pattern);
}

/*
 * Loads the default cover and resizes it into
 * a certain size. If the size is -1 the cover
 * does not get resized.
 *
 * :param size: size, default -1
 * :return: default cover
 */
QPixmap Utils::defaultCover(int size)
{
    QPixmap pixmap(IMG_DEFAULT_COVER);
    if (size != -1)
        return Utils::resize(pixmap, size);
    else
        return pixmap;
}

/*
 * Resizes a pixmap.
 *
 * :param pixmap: pixmap
 * :param size: size
 * :return: scaled pixmap
 */
QPixmap Utils::resize(const QPixmap &pixmap, int size)
{
    return pixmap.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

/*
 * Resizes an image.
 *
 * :param image: image
 * :param size: size
 * :return: scaled image
 */
QImage Utils::resize(const QImage &image, int size)
{
    return image.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

/*
 * Loads custom font.
 *
 * :return: font
 */
QFont Utils::loadFont()
{
    int id = QFontDatabase::addApplicationFont(FONT_LATO);
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);

    QFont font(family);
    font.setPointSizeF(Config::App::fontSize());
    font.setWeight(QFont::Weight::Medium);

    return font;
}

/*
 * Reads a file and returns its content. If the
 * file cannot be opened or read, an empty
 * string gets returned.
 *
 * :param path: file
 * :return: file content, empty string at failure
 */
QString Utils::read(const QString &path)
{
    QFile file(path);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        Logger::log("FileUtil: Cannot read file '%1'", path);
        return QString();
    }

    QTextStream stream(&file);
    QString text = stream.readAll();
    file.close();

    return text;
}

/*
 * Checks if a file exists.
 *
 * :param path: file
 * :return: file exists
 */
bool Utils::exists(const QString &path)
{
    return QFileInfo(path).exists();
}

/*
 * Returns the directory for a given path. If the
 * path is a directory it will get returned. If
 * it is a file, the directory of the file gets
 * returned.
 *
 * :param path: path
 * :return: directory, empty dir at failure
 */
QDir Utils::dir(const QString &path)
{
    QFileInfo info(path);

    if (info.isDir())
        return QDir(path);

    if (info.isFile())
        return info.absoluteDir();

    return QDir();
}

/*
 * Globbes files with a certain pattern. Behaves
 * very simular to Pythons glob function.
 *
 * :param path: path
 * :param pattern: pattern
 * :param recursive: glob resursively
 * :return: list of paths
 */
QStringList Utils::glob(const QString &path, const QString &pattern, bool recursive)
{
    QDir dir = Utils::dir(path);
    QStringList filter;
    filter << pattern;
    QStringList result;

    QFileInfoList infos = dir.entryInfoList(filter, QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files);
    for (const QFileInfo &info : infos)
    {
        if (info.isDir() && recursive)
            result << glob(info.absoluteFilePath(), pattern, recursive);

        if (info.isFile())
            result << info.absoluteFilePath();
    }
    return result;
}

/*
 * Returns the file name of a file.
 *
 * :param file: file
 * :return: file name
 */
QString Utils::fileName(const QString &file)
{
    return QFileInfo(file).baseName();
}

/*
 * Checks if all resources are available.
 */
void Utils::checkResources()
{
    QStringList resources =
    {
        FONT_LATO,
        ICO_LOOP,
        ICO_NEXT,
        ICO_PAUSE,
        ICO_PLAY,
        ICO_PREVIOUS,
        ICO_SHUFFLE,
        ICO_VOLUME_FULL,
        ICO_VOLUME_LOW,
        ICO_VOLUME_MEDIUM,
        ICO_VOLUME_MUTE,
        IMG_DEFAULT_COVER,
        IMG_EGGPLAYER
    };

    for (const QString &resource : resources)
        if (!Utils::exists(resource))
            Logger::log("Resource does not exist '%1'", resource);
}

/*
 * This function returns the egg player documents
 * directory and creates it if it does not exist
 * already.
 *
 * :return: directory
 */
QString Utils::documents()
{
    QString directory = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/egg-player";
    QDir().mkpath(directory);

    return directory;
}

/*
 * Calculates dominent color of an image. The
 * algorithm iterates over every pixel, converts
 * them into the HSV color space and creates two
 * mapped heuristics out of them.
 * Those hold colorful and grey scale colors. The
 * algorithm tries to return a colorful color. If
 * there is none, a grey scale gets returned.
 *
 * :param image: image
 * :return: dominant color
 */
QColor Utils::dominantColor(const QImage &image)
{
    // Map 360 hues to RANGE
    const quint32 RANGE = 60;

    // Initialize arrays for colorful colors
    std::array<quint32, RANGE> cCounts;
    std::array<quint32, RANGE> cHues;
    std::array<quint32, RANGE> cSaturations;
    std::array<quint32, RANGE> cValues;

    // Initialize arrays for grey scale colors
    std::array<quint32, RANGE> gCounts;
    std::array<quint32, RANGE> gHues;
    std::array<quint32, RANGE> gSaturations;
    std::array<quint32, RANGE> gValues;

    // Fill arrays
    for (quint32 i = 0; i < RANGE; i++)
    {
        cCounts[i] = 0;
        cHues[i] = 0;
        cSaturations[i] = 0;
        cValues[i] = 0;

        gCounts[i] = 0;
        gHues[i] = 0;
        gSaturations[i] = 0;
        gValues[i] = 0;
    }

    QRgb *pixels = (QRgb *) image.bits();
    quint32 pixelCount = image.height() * image.width();
    for (quint32 i = 0; i < pixelCount; i++)
    {
        QColor rgb = QColor(pixels[i]);
        qint32 red = rgb.red();
        qint32 green = rgb.green();
        qint32 blue = rgb.blue();

        QColor hsv = rgb.toHsv();
        quint32 hue = hsv.hsvHue() == -1 ? 0 : rgb.hsvHue();
        quint32 saturation = hsv.hsvSaturation();
        quint32 value = hsv.value();

        quint32 index = hue / (360 / RANGE);

        // Check if color is a grey scale or colorful
        if (qAbs(red - green) < 25 && qAbs(green - blue) < 25 && qAbs(red - blue) < 25)
        {
            gCounts[index]++;
            gHues[index] += hue;
            gSaturations[index] += saturation;
            gValues[index] += value;
        }
        else
        {
            cCounts[index]++;
            cHues[index] += hue;
            cSaturations[index] += saturation;
            cValues[index] += value;
        }
    }

    // Try to get the dominant colorful color
    quint32 index = 0;
    quint32 max = 0;
    for (quint32 i = 0; i < RANGE; i++)
    {
        quint32 temp = cHues[i] + 2 * cSaturations[i] + 3 * cValues[i];
        if (temp > max)
        {
            index = i;
            max = temp;
        }
    }

    if (cCounts[index] != 0)
    {
        quint32 hue = cHues[index] / cCounts[index];
        quint32 saturation = cSaturations[index] / cCounts[index];
        quint32 value = cValues[index] / cCounts[index];

        return QColor::fromHsv(hue, saturation, value);
    }
    else
    {
        // Choose a grey scale instead
        index = 0;
        max = 0;
        for (quint32 i = 0; i < RANGE; i++)
        {
            quint32 temp = gHues[i] + 2 * gSaturations[i] + 3 * gValues[i];
            if (temp > max)
            {
                index = i;
                max = temp;
            }
        }

        quint32 hue = gHues[index] / gCounts[index];
        quint32 saturation = gSaturations[index] / gCounts[index];
        quint32 value = gValues[index] / gCounts[index];

        return QColor::fromHsv(hue, saturation, value);
    }
}

/*
 * Gets the dominant color of an image and edits
 * some values to prevent too bright values. It
 * also resizes the image to keep processing the
 * constant.
 *
 * :param image: image
 * :param size: size for scaling, default 25
 * :return: background color
 */
QColor Utils::backgroundColor(const QImage &image, quint32 size)
{
    QColor color = dominantColor(image.scaled(size, size));

    qreal hue = color.hsvHueF();
    qreal saturation = color.hsvSaturationF();
    qreal value = color.valueF();

    value = qMin(value, 0.36);
    saturation = qMin(saturation, 0.8);

    color = QColor::fromHsvF(hue, saturation, value);

    return color.toRgb();
}

/*
 * Overloaded function.
 *
 * :param image: image
 * :param size: size for scaling
 * :return: background color
 */
QColor Utils::backgroundColor(const QPixmap &image, quint32 size)
{
    return backgroundColor(image.toImage(), size);
}
