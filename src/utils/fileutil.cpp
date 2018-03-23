#include "fileutil.hpp"

QString FileUtil::read(QString path)
{
    QFile file(path);

    if (!file.open(QFile::ReadOnly | QFile::Text))
        return QString();

    QTextStream stream(&file);
    QString text = stream.readAll();

    file.close();

    return text;
}

bool FileUtil::exists(QString path)
{
    return QFileInfo(path).exists();
}

QDir FileUtil::dir(QString path)
{
    QFileInfo info(path);
    if (info.isDir())
        return QDir(path);
    if (info.isFile())
        return info.absoluteDir();
    return QDir();
}

QString FileUtil::join(QDir dir, QString path)
{
    return dir.filePath(path);
}

QString FileUtil::join(QString path1, QString path2)
{
    return join(FileUtil::dir(path1), path2);
}

QStringList FileUtil::glob(const QString &path, QString pattern, bool recursive)
{
    QDir dir = FileUtil::dir(path);
    QStringList filter;
    filter << pattern;
    QStringList result;

    QFileInfoList infoList = dir.entryInfoList(filter, QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files);

    for (QFileInfo info : infoList)
    {
        if (info.isDir() && recursive)
        {
            QString sub = info.absoluteFilePath();
            result << glob(sub, pattern, recursive);
        }
        if (info.isFile())
            result << info.absoluteFilePath();
    }
    return result;
}
