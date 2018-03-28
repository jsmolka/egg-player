#include "fileutil.hpp"

QString FileUtil::read(const QString &path)
{
    QFile file(path);

    if (!file.open(QFile::ReadOnly | QFile::Text))
        return QString();

    QTextStream stream(&file);
    QString text = stream.readAll();

    file.close();

    return text;
}

bool FileUtil::exists(const QString &path)
{
    return QFileInfo(path).exists();
}

QDir FileUtil::dir(const QString &path)
{
    QFileInfo info(path);

    if (info.isDir())
        return QDir(path);

    if (info.isFile())
        return info.absoluteDir();

    return QDir();
}

QString FileUtil::join(const QDir &dir, const QString &path)
{
    return dir.filePath(path);
}

QString FileUtil::join(const QString &path1, const QString &path2)
{
    return join(FileUtil::dir(path1), path2);
}

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
