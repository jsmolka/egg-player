#include "fileutil.hpp"

bool FileUtil::exists(const QString &file)
{
    return QFileInfo(file).exists();
}

QString FileUtil::fileName(const QString &file)
{
    return QFileInfo(file).baseName();
}

QString FileUtil::read(const QString &file, const QString &defaultValue)
{
    QFile qFile(file);
    if (!qFile.open(QFile::ReadOnly | QFile::Text))
        return defaultValue;

    return QTextStream(&qFile).readAll();
}

QByteArray FileUtil::readBytes(const QString &file, const QByteArray &defaultValue)
{
    QFile qFile(file);
    if (!qFile.open(QFile::ReadOnly | QFile::Text))
        return defaultValue;

    return qFile.readAll();
}

void FileUtil::write(const QString &file, const QString &content)
{
    QFile qFile(file);
    if (!qFile.open(QFile::WriteOnly))
        return;

    QTextStream(&qFile) << content;
}

void FileUtil::write(const QString &file, const QByteArray &content)
{
    QFile qFile(file);
    if (!qFile.open(QFile::WriteOnly))
        return;

    qFile.write(content);
}

Files FileUtil::glob(const QString &path, const QString &filter)
{
    Files result;

    QDirIterator iterator(path, QStringList() << filter, QDir::Files, QDirIterator::Subdirectories);
    while (iterator.hasNext())
    {
        iterator.next();
        result << iterator.filePath();
    }
    return result;
}

QString FileUtil::Css::bar()
{
    return FileUtil::read(CSS_BAR)
        .replace("groove-height", QString::number(cfgBar->grooveHeight()))
        .replace("handle-size-half", QString::number(cfgBar->handleSize() / 2))
        .replace("handle-size", QString::number(cfgBar->handleSize()))
        .replace("icon-size-half", QString::number(cfgBar->iconSize() / 2));
}

QString FileUtil::Css::egg()
{
    return FileUtil::read(CSS_EGG);
}

QString FileUtil::Css::library()
{
    return FileUtil::read(CSS_LIBRARY)
        .replace("cell-padding", QString::number(cfgLibrary->cellPadding()))
        .replace("scrollbar-width", QString::number(cfgLibrary->scrollBarWidth()));
}
