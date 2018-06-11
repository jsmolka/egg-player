#include "fileutil.hpp"

bool FileUtil::exists(const QString &file)
{
    return QFileInfo(file).exists();
}

QString FileUtil::fileName(const QString &file)
{
    return QFileInfo(file).baseName();
}

quint64 FileUtil::size(const QString &file)
{
    return QFileInfo(file).size();
}

QString FileUtil::read(const QString &file)
{
    QFile qFile(file);
    if (!qFile.open(QFile::ReadOnly | QFile::Text))
        return QString();

    QTextStream stream(&qFile);
    return stream.readAll();
}

StringList FileUtil::glob(const QString &path, const QString &suffix)
{
    StringList result;
    QDirIterator iterator(path, QDirIterator::Subdirectories);

    while (iterator.hasNext())
    {
        iterator.next();
        if (iterator.fileInfo().isFile() && iterator.fileInfo().suffix().compare(suffix, Qt::CaseInsensitive) == 0)
            result << iterator.filePath();
    }
    return result;
}
