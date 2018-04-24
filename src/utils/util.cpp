#include "util.hpp"

/*
 * Converts a length in seconds
 * into a time string.
 *
 * :param length: length in seconds
 * :return: time string
 */
QString Util::timeString(int length)
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
