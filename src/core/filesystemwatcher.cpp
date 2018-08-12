#include "filesystemwatcher.hpp"

FileSystemWatcher::FileSystemWatcher(QObject *parent)
    : QObject(parent)
    , m_watcher(this)
    , m_fileTimer(this)
    , m_dirTimer(this)
    , m_bufferDuration(200)
{
    connect(&m_watcher, &QFileSystemWatcher::fileChanged, this, &FileSystemWatcher::onWatcherFileChanged);
    connect(&m_watcher, &QFileSystemWatcher::directoryChanged, this, &FileSystemWatcher::onWatcherDirChanged);

    connect(&m_fileTimer, &QTimer::timeout, this, &FileSystemWatcher::onFileTimerTimeout);
    connect(&m_dirTimer, &QTimer::timeout, this, &FileSystemWatcher::onDirTimerTimeout);
}

FileSystemWatcher::~FileSystemWatcher()
{

}

Files FileSystemWatcher::globAudios(const QString &path)
{
    Files result;

    QDirIterator iter(path, QStringList() << "*.mp3", QDir::Files, QDirIterator::Subdirectories);
    while (iter.hasNext())
    {
        iter.next();
        result << iter.filePath();
    }
    return result;
}

void FileSystemWatcher::setBufferDuration(int duration)
{
    m_bufferDuration = duration;
}

int FileSystemWatcher::bufferDuration() const
{
    return m_bufferDuration;
}

void FileSystemWatcher::watchAudio(Audio *audio)
{
    m_watcher.addPath(audio->path());
    m_audios.insert(audio->path(), audio);
    m_sizes.insert(audio->info().size(), audio);
}

void FileSystemWatcher::watchDir(const QString &dir)
{
    QStringList paths;
    paths << dir;

    QDirIterator iter(dir, QDir::Dirs | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while (iter.hasNext())
    {
        iter.next();
        paths << iter.filePath();
        m_dirs << iter.filePath();
    }
    m_watcher.addPaths(paths);
}

void FileSystemWatcher::onWatcherFileChanged(const QString &file)
{
    m_fileBuffer << file;
    m_fileTimer.start(m_bufferDuration);
}

void FileSystemWatcher::onWatcherDirChanged(const QString &dir)
{
    m_dirBuffer << dir;
    m_dirTimer.start(m_bufferDuration);
}

void FileSystemWatcher::onFileTimerTimeout()
{
    m_fileTimer.stop();

    for (const QString &file : m_fileBuffer)
        fileChanged(file);

    m_fileBuffer.clear();
}

void FileSystemWatcher::onDirTimerTimeout()
{
    m_dirTimer.stop();

    for (const QString &dir : m_dirBuffer)
        dirChanged(dir);

    m_dirBuffer.clear();
}

void FileSystemWatcher::fileChanged(const QString &file)
{
    Audio *audio = m_audios.value(file);
    const QFileInfo info = audio->info();

    if (info.exists())
        return eventModified(audio);

    const QString dir = info.dir().absolutePath();
    QDirIterator iter(dir, QStringList() << "*.mp3", QDir::Files);
    while (iter.hasNext())
    {
        iter.next();
        if (!m_audios.contains(iter.filePath()))
        {
            if (m_sizes.contains(iter.fileInfo().size()))
                return eventRenamed(audio, iter.filePath());
        }
    }
    return eventRemoved(audio);
}

void FileSystemWatcher::dirChanged(const QString &dir)
{
    parseDirectory(dir, true);
}

void FileSystemWatcher::parseDirectory(const QString &dir, bool isRoot)
{
    QDirIterator iter(dir, QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    while (iter.hasNext())
    {
        iter.next();
        const QString filePath = iter.filePath();
        const QFileInfo info = iter.fileInfo();
        if (info.isDir())
        {
            if (isRoot || !m_dirs.contains(filePath))
                parseDirectory(filePath);
        }
        else
        {
            if (filePath.endsWith(".mp3"))
            {
                if (!m_audios.contains(filePath))
                {
                    if (m_sizes.contains(info.size()))
                    {
                        Audio *audio = m_sizes.value(info.size());
                        if (audio)
                            eventRenamed(m_sizes.value(info.size()), filePath);
                        else
                            eventAdded(filePath);
                    }
                    else
                    {
                        eventAdded(filePath);
                    }
                }
            }
        }
    }
}

void FileSystemWatcher::eventAdded(const QString &file)
{
    emit added(file);
}

void FileSystemWatcher::eventRemoved(Audio *audio)
{
    m_watcher.removePath(audio->path());
    m_audios.remove(audio->path());
    m_sizes.remove(m_sizes.key(audio));

    emit removed(audio);
}

void FileSystemWatcher::eventModified(Audio *audio)
{
    emit modified(audio);
}

void FileSystemWatcher::eventRenamed(Audio *audio, const QString &file)
{
    m_watcher.removePath(audio->path());
    m_watcher.addPath(file);

    m_audios.remove(audio->path());
    m_audios.insert(file, audio);

    qint64 size = m_sizes.key(audio);
    m_sizes.insert(size, audio);

    emit renamed(audio, file);
}
