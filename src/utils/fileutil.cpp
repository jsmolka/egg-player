#include "fileutil.hpp"

/*
 * Read a  file.
 *
 * :param path: file
 * :return: file content or empty string
 */
QString FileUtil::read(const QString &path)
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
 * Checks if file exists.
 *
 * :param path: file
 * :return: file exists
 */
bool FileUtil::exists(const QString &path)
{
    return QFileInfo(path).exists();
}

/*
 * Gets either dir of dir or
 * dir of file.
 *
 * :param path: file
 * :return: directory
 */
QDir FileUtil::dir(const QString &path)
{
    QFileInfo info(path);

    if (info.isDir())
        return QDir(path);

    if (info.isFile())
        return info.absoluteDir();

    return QDir();
}

/*
 * Globbes files with a certain pattern.
 * Behaves simular to Pythons glob function.
 *
 * :param path: path to search in
 * :param pattern: patter to apply
 * :param recursive: search dir resursively
 * :return: list of paths
 */
QStringList FileUtil::glob(const QString &path, const QString &pattern, bool recursive)
{
    QDir dir = FileUtil::dir(path);
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
 * Returns file name of file.
 *
 * :param file: file
 * :return: file name
 */
QString FileUtil::fileName(const QString &file)
{
    return QFileInfo(file).baseName();
}
