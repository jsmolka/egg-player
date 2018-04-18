#include "fileutil.hpp"

QString FileUtil::read(const QString &path)
{
    QFile file(path);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        Logger::log(QString("Failed reading file: '%1'").arg(path));
        return QString();
    }

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

QString FileUtil::fileName(const QString &file)
{
    return QFileInfo(file).baseName();
}
