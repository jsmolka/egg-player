#include "utils.hpp"

/*
 * Converts a length in seconds into a time string.
 *
 * :param length: length in seconds
 * :return: time string
 */
QString Util::time(int length)
{
    int seconds = length % 60;
    int minutes = length / 60 % 60;
    int hours = length / 3600 % 60;

    QString format;
    if (hours > 9)
        format = "hh:mm:ss";
    else if (hours > 0)
        format = "h:mm:ss";
    else if (minutes > 9)
        format = "mm:ss";
    else
        format = "m:ss";

    return QTime(hours, minutes, seconds).toString(format);
}

/*
 * Loads the default cover and resizes it to a certain size.
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
 * :param fast: fast, default false
 * :return: scaled pixmap
 */
QPixmap Util::resize(const QPixmap &pixmap, int size, bool fast)
{
    return pixmap.scaled(size, size, Qt::KeepAspectRatio, fast ? Qt::FastTransformation : Qt::SmoothTransformation);
}

/*
 * Resizes an image.
 *
 * :param image: image
 * :param size: size
 * :param fast: fast, default false
 * :return: scaled image
 */
QImage Util::resize(const QImage &image, int size, bool fast)
{
    return image.scaled(size, size, Qt::KeepAspectRatio, fast ? Qt::FastTransformation : Qt::SmoothTransformation);
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

    QVector<StringList> result;
    for (int i = 0; i < n; i++)
    {
        int l = i * quo + qMin(i, rem);
        int r = (i + 1) * quo + qMin(i + 1, rem);
        result << list.mid(l, r - l);
    }
    return result;
}

/*
 * Reads a file and returns its content.
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
 * Calculates the dominant color of an image by creating heuristics for the HSV
 * color space. If no colorful color can be found, a grey scale will be returned.
 *
 * :param image: image
 * :return: dominant color
 */
QColor ColorUtil::dominant(const QImage &image)
{
    const quint32 RANGE = 60;

    quint32 cCounts[RANGE] = {};
    quint32 cHues[RANGE] = {};
    quint32 cSaturations[RANGE] = {};
    quint32 cValues[RANGE] = {};

    quint32 gCounts[RANGE] = {};
    quint32 gHues[RANGE] = {};
    quint32 gSaturations[RANGE] = {};
    quint32 gValues[RANGE] = {};

    QRgb *pixels = (QRgb *) image.bits();
    quint32 pixelCount = image.height() * image.width();
    for (quint32 i = 0; i < pixelCount; i++)
    {
        QColor rgb = QColor(pixels[i]);
        qint32 red = rgb.red();
        qint32 green = rgb.green();
        qint32 blue = rgb.blue();

        QColor hsv = rgb.toHsv();
        qint32 hue = qMax(0, hsv.hsvHue());
        qint32 saturation = hsv.hsvSaturation();
        qint32 value = hsv.value();

        quint32 index = hue / (360 / RANGE);

        const qint32 limit = 25;
        if (qAbs(red - green) < limit && qAbs(green - blue) < limit && qAbs(red - blue) < limit)
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
 * Tries to load a cached value if the id is valid.
 *
 * :param image: image
 * :param id: id, default -1
 * :return: background color
 */
QColor ColorUtil::background(const QImage &image, int id)
{
    if (id != -1)
        if (_colorCache.contains(id))
            return _colorCache.value(id);

    QColor color = dominant(Util::resize(image, 25, true));
    qreal hue = color.hsvHueF();
    qreal saturation = qMin(color.hsvSaturationF(), 0.8);
    qreal value = qMin(color.valueF(), 0.36);
    color = QColor::fromHsvF(hue, saturation, value);

    if (id != -1)
        _colorCache[id] = color;

    return color;
}

/*
 * Overloaded function.
 *
 * :param pixmap: pixmap
 * :param id: id, default -1
 * :return: background color
 */
QColor ColorUtil::background(const QPixmap &pixmap, int id)
{
    return background(pixmap.toImage(), id);
}

/*
 * Background color cache.
 */
QHash<int, QColor> ColorUtil::_colorCache;
