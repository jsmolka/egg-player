#include "fileutil.hpp"

QString FileUtil::read(QString path)
{
    QFile file(path);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Could not read file: " << path;
        return QString();
    }

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
    return QDir(path).current();
}

QString FileUtil::join(QDir dir, QString path)
{
    return dir.current().filePath(path);
}

QString FileUtil::join(QString path1, QString path2)
{
    return join(QDir(path1), path2);
}
