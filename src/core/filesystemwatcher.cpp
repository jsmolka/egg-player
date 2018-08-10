#include "filesystemwatcher.hpp"

FileSystemWatcher::FileSystemWatcher(QObject *parent)
    : QObject(parent)
    , m_watcher(this)
{
    connect(&m_watcher, &QFileSystemWatcher::fileChanged, this, &FileSystemWatcher::onWatcherFileChanged);
    connect(&m_watcher, &QFileSystemWatcher::directoryChanged, this, &FileSystemWatcher::onWatcherDirectoryChanged);
}

FileSystemWatcher::~FileSystemWatcher()
{

}

Files FileSystemWatcher::globFiles(const QString &path, const QString &filter, bool recursive)
{
    Files result;

    QDirIterator::IteratorFlag flags = recursive ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags;
    QDirIterator iter(path, QStringList() << filter, QDir::Files, flags);
    while (iter.hasNext())
    {
        iter.next();
        result << iter.filePath();
    }
    return result;
}

Files FileSystemWatcher::globAudios(const QString &path, bool recursive)
{
    return globFiles(path, "*.mp3", recursive);
}

Paths FileSystemWatcher::globDirs(const QString &path, bool recursive)
{
    Paths result;

    QDirIterator::IteratorFlag flags = recursive ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags;
    QDirIterator iter(path, QDir::Dirs, flags);
    while (iter.hasNext())
    {
        iter.next();
        result << iter.path();
    }
    return result;
}

void FileSystemWatcher::watch(Audio *audio)
{
    QFileInfo info = audio->info();

    QStringList paths;
    paths << audio->path();

    QString dir = info.absoluteDir().absolutePath();
    if (!m_dirs.contains(dir))
    {
        m_dirs.insert(dir, dirCount(dir));
        paths << dir;
    }

    m_watcher.addPaths(paths);
    m_audios.insert(audio->path(), audio);
    m_sizes.insert(info.size(), audio);
}

void FileSystemWatcher::onWatcherFileChanged(const QString &file)
{
    Audio *audio = m_audios.value(file);

    if (audio->info().exists())
        return emitModified(audio);

    QString dir = audio->info().dir().absolutePath();
    QDirIterator iter(dir, QStringList() << "*.mp3", QDir::Files);
    while (iter.hasNext())
    {
        iter.next();
        QString path = iter.filePath();
        if (!m_audios.contains(path))
        {
            if (m_sizes.contains(iter.fileInfo().size()))
                return emitRenamed(audio, path);
        }
    }
    return emitRemoved(audio);
}

void FileSystemWatcher::onWatcherDirectoryChanged(const QString &directory)
{
    qDebug() << "Dir changed:" << directory;
}

void FileSystemWatcher::emitAdded(const QString &file)
{
    qDebug() << "added" << file;
    emit added(file);
}

void FileSystemWatcher::emitRemoved(Audio *audio)
{
    qDebug() << "removed" << audio->path();
    m_audios.remove(audio->path());

    emit removed(audio);
}

void FileSystemWatcher::emitModified(Audio *audio)
{
    qDebug() << "modified" << audio->path();
    emit modified(audio);
}

void FileSystemWatcher::emitRenamed(Audio *audio, const QString &file)
{
    qDebug() << "renamed" << audio->path() << "to" << file;
    m_audios.remove(audio->path());
    m_audios.insert(file, audio);

    emit renamed(audio, file);
}

int FileSystemWatcher::dirCount(const QString &dir)
{
    return globDirs(dir, false).size();
}
