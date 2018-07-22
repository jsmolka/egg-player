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

    return QTextStream(&qFile).readAll();
}

Files FileUtil::glob(const QString &path, const QString &suffix)
{
    Files result;

    QDirIterator iterator(path, QDirIterator::Subdirectories);
    while (iterator.hasNext())
    {
        iterator.next();
        if (iterator.fileInfo().isFile() && iterator.fileInfo().suffix().compare(suffix, Qt::CaseInsensitive) == 0)
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
