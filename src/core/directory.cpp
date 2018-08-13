#include "directory.hpp"

Directory::Directory(QObject *parent)
    : Directory(QString(), parent)
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

Path Directory::path() const
{
    return m_path;
}

Files Directory::files() const
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
            connect(dir, &Directory::created, this, &Directory::created);
            dir->parse();
            m_dirs << dir;
        }
        else
        {
            if (iter.filePath().endsWith("mp3", Qt::CaseInsensitive))
                m_files << iter.filePath();
        }
    }
    emit created(this);
}
