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
