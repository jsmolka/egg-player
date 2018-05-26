#include "fileutil.hpp"

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
