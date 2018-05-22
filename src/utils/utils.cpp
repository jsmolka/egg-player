#include "utils.hpp"

/*
 * Converts a length in seconds into a time string. If automatically uses the
 * correct format depending on the length.
 *
 * :param length: length in seconds
 * :return: time string
 */
QString Util::time(int length)
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
 * Loads the default cover and resizes it to a certain size. If the size is -1
 * the cover does not get resized.
 *
 * :param size: size, default -1
 * :return: default cover
 */
QPixmap Util::cover(int size)
{
    QPixmap pixmap(IMG_DEFAULT_COVER);
    if (size != -1)
        return Util::resize(pixmap, size);
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
QPixmap Util::resize(const QPixmap &pixmap, int size)
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
QImage Util::resize(const QImage &image, int size)
{
    return image.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

/*
 * Chunks a list into n evenly sized parts.
 *
 * :param list: list
 * :param n: n
 * :return: chunked list
 */
QVector<StringList> Util::chunk(const StringList &list, int n)
{
    n = qMin(qMax(1, n), list.size());
    int quo = list.size() / n;
    int rem = list.size() % n;

    QVector<int> indices;
    for (int i = 0; i < n + 1; i++)
        indices << quo * i + qMin(i, rem);

    QVector<StringList> result;
    for (int i = 0; i < n; i++)
    {
        int left = indices[i];
        int right = indices[i + 1];
        result << list.mid(left, right - left);
    }
    return result;
}

/*
 * Reads a file and returns its content. If the file cannot be opened or read,
 * an empty string gets returned.
 *
 * :param path: path
 * :return: file content
 */
QString FileUtil::read(const QString &file)
{
    QFile qFile(file);
    if (!qFile.open(QFile::ReadOnly | QFile::Text))
        return QString();

    QTextStream stream(&qFile);
    return stream.readAll();
}

/*
 * Checks if a file exists.
 *
 * :param path: file
 * :return: exists
 */
bool FileUtil::exists(const QString &path)
{
    return QFileInfo(path).exists();
}

/*
 * Returns the file name of a file.
 *
 * :param file: file
 * :return: file name
 */
QString FileUtil::fileName(const QString &file)
{
    return QFileInfo(file).baseName();
}

/*
 * Globbes files with a certain suffix.
 *
 * :param path: path
 * :param suffix: suffix
 * :return: list of paths
 */
StringList FileUtil::glob(const QString &path, const QString &suffix)
{
    StringList result;
    QDirIterator iterator(path, QDirIterator::Subdirectories);
    while (iterator.hasNext())
    {
        iterator.next();
        if (iterator.fileInfo().isFile())
            if (iterator.fileInfo().suffix().compare(suffix, Qt::CaseInsensitive) == 0)
                result << iterator.filePath();
    }
    return result;
}

/*
 * Calculates dominent color of an image. The algorithm iterates over every
 * pixel, converts them into the HSV color space and creates two mapped
 * heuristics out of them.
 * Those hold colorful and grey scale colors. The algorithm tries to return a
 * colorful color. If there is none, a grey scale gets returned.
 *
 * :param image: image
 * :return: dominant color
 */
QColor ColorUtil::dominant(const QImage &image)
{
    const quint32 RANGE = 60;

    std::array<quint32, RANGE> cCounts;
    std::array<quint32, RANGE> cHues;
    std::array<quint32, RANGE> cSaturations;
    std::array<quint32, RANGE> cValues;

    std::array<quint32, RANGE> gCounts;
    std::array<quint32, RANGE> gHues;
    std::array<quint32, RANGE> gSaturations;
    std::array<quint32, RANGE> gValues;

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
 * Gets the dominant color of an image and edits some values to prevent too
 * bright values. It also resizes the image to keep processing the constant.
 *
 * :param image: image
 * :param size: size for scaling, default 25
 * :return: background color
 */
QColor ColorUtil::background(const QImage &image, quint32 size)
{
    QColor color = dominant(image.scaled(size, size));

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
QColor ColorUtil::background(const QPixmap &image, quint32 size)
{
    return background(image.toImage(), size);
}
