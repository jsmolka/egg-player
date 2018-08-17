#include "directory.hpp"

Directory::Directory(QObject *parent)
    : Directory(Path(), parent)
{

}

Directory::Directory(const Path &path, QObject *parent)
    : QObject(parent)
    , m_path(path)
{

}

Directory::~Directory()
{

}

void Directory::setPath(const Path &path)
{
    m_path = path;
}

Path Directory::path() const
{
    return m_path;
}

QSet<File> Directory::files() const
{
    return m_files;
}

DirectoryVector Directory::dirs() const
{
    return m_dirs;
}

void Directory::parse()
{
    QDirIterator iter(m_path, QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    while (iter.hasNext())
    {
        iter.next();
        if (iter.fileInfo().isDir())
        {
            Directory *dir = new Directory(iter.filePath(), this);
            connect(dir, &Directory::parsed, this, &Directory::parsed);
            dir->parse();
            m_dirs << dir;
        }
        else
        {
            if (iter.filePath().endsWith("mp3", Qt::CaseInsensitive))
                m_files << iter.filePath();
        }
    }
    emit parsed(this);
}

Files Directory::processChanges()
{
    Files result;

    for (Directory *dir : m_dirs)
        result << dir->processChanges();

    if (!QFileInfo(m_path).exists())
    {
        for (const File &file : m_files)
            result << file;
    }
    else
    {
        for (const File &file : m_files)
        {
            if (!QFileInfo(file).exists())
            {
                result << file;
                m_files.remove(file);
            }
        }

        QDirIterator iter(m_path, QStringList() << "*.mp3", QDir::Files);
        while (iter.hasNext())
        {
            iter.next();
            const File file = iter.filePath();
            if (!m_files.contains(file))
            {
                result << file;
                m_files.insert(file);
            }
        }
    }
    return result;
}
