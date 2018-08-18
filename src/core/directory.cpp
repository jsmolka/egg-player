#include "directory.hpp"

Directory::Directory(QObject *parent)
    : Directory(Path(), parent)
{

}

Directory::Directory(const Path &path, QObject *parent)
    : QObject(parent)
    , m_path(path)
    , m_files()
    , m_dirs()
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

QHash<Path, Directory *> Directory::dirs() const
{
    return m_dirs;
}

bool Directory::exists() const
{
    return QDir(m_path).exists();
}

void Directory::parse()
{
    QDirIterator iter(m_path, QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    while (iter.hasNext())
    {
        iter.next();
        const File file = iter.filePath();
        if (iter.fileInfo().isDir())
        {
            Directory *dir = new Directory(file, this);
            connect(dir, &Directory::parsed, this, &Directory::parsed);
            connect(dir, &Directory::created, this, &Directory::created);
            connect(dir, &Directory::removed, this, &Directory::removed);
            dir->parse();
            m_dirs.insert(file, dir);
        }
        else
        {
            if (file.endsWith("mp3", Qt::CaseInsensitive))
                m_files << file;
        }
    }
    emit parsed(this);
}

Files Directory::processChanges()
{
    Files changes;

    processDirChanges(changes);
    processFileChanges(changes);

    return changes;
}

void Directory::processDirChanges(Files &changes)
{
    QHashIterator<Path, Directory *> hashIter(m_dirs);
    while (hashIter.hasNext())
    {
        hashIter.next();
        Directory *dir = hashIter.value();
        if (!dir->exists())
        {
            for (const File &file : dir->files())
                changes << file;

            emit removed(dir);
            m_dirs.remove(dir->path());
        }
    }

    QDirIterator dirIter(m_path, QDir::Dirs | QDir::NoDotAndDotDot);
    while (dirIter.hasNext())
    {
        dirIter.next();
        const Path path = dirIter.filePath();
        Directory *dir = m_dirs.value(path, nullptr);
        if (!dir)
        {
            dir = new Directory(path, this);
            connect(dir, &Directory::created, this, &Directory::created);
            connect(dir, &Directory::removed, this, &Directory::removed);
            m_dirs.insert(path, dir);
            emit created(dir);
        }
        changes << dir->processChanges();
    }
}

void Directory::processFileChanges(Files &changes)
{
    if (!QFileInfo(m_path).exists())
    {
        for (const File &file : m_files)
            changes << file;

        emit removed(this);
    }
    else
    {
        QMutableSetIterator<File> setIter(m_files);
        while (setIter.hasNext())
        {
            setIter.next();
            if (!QFileInfo(setIter.value()).exists())
            {
                changes << setIter.value();
                setIter.remove();
            }
        }

        QDirIterator fileIter(m_path, QStringList() << "*.mp3", QDir::Files);
        while (fileIter.hasNext())
        {
            fileIter.next();
            const File file = fileIter.filePath();
            if (!m_files.contains(file))
            {
                changes << file;
                m_files.insert(file);
            }
        }
    }
}
