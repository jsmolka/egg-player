#include "filesystem.hpp"

FileSystem::FileSystem(QObject *parent)
    : QObject(parent)
    , m_watcher(this)
{
    connect(&m_watcher, &FileSystemWatcher::fileChanged, this, &FileSystem::onFileChanged);
    connect(&m_watcher, &FileSystemWatcher::directoryChanged, this, &FileSystem::onDirectoryChanged);
}

FileSystem::~FileSystem()
{

}

QHash<Path, Directory *> FileSystem::dirs() const
{
    return m_dirs;
}

void FileSystem::addPath(const Path &path)
{
    Directory *dir = new Directory(path, this);
    connect(dir, &Directory::parsed, this, &FileSystem::onDirParsed);
    dir->parse();
}

Files FileSystem::globAudios() const
{
    Files result;
    QHashIterator<Path, Directory *> iter(m_dirs);
    while (iter.hasNext())
    {
        iter.next();
        for (const File &file : iter.value()->files())
            result << file;
    }
    // Todo: Maybe reserve space here to const inserting time
    return result;
}

void FileSystem::eventModified(const File &file)
{
    qDebug() << "modified" << file;
}

void FileSystem::eventRenamed(const File &from, const File &to)
{
    qDebug() << "renamed" << from << "to" << to;
}

void FileSystem::eventAdded(const File &file)
{
    qDebug() << "added" << file;
}

void FileSystem::eventRemoved(const File &file)
{
    qDebug() << "removed" << file;
}

void FileSystem::onDirParsed(Directory *dir)
{
    QStringList paths;
    for (const File &file : dir->files())
    {
        paths << file;
        m_unique.insert(file, uniqueInfo(file));
    }
    paths << dir->path();

    m_watcher.addPaths(paths);
    m_dirs.insert(dir->path(), dir);
}

void FileSystem::onFileChanged(const File &file)
{
    if (QFileInfo(file).exists())
        eventModified(file);
}

void FileSystem::onDirectoryChanged(const Path &dir)
{
    const Files files = m_dirs.value(dir)->processChanges();
    QHash<UniqueInfo, File> renamedFrom;
    QHash<UniqueInfo, File> renamedTo;
    for (const File file : files)
    {
        if (m_unique.contains(file))
        {
            renamedFrom.insert(m_unique.value(file), file);
        }
        else
        {
            const UniqueInfo info = uniqueInfo(file);
            renamedTo.insert(info, file);
        }
    }

    QHashIterator<UniqueInfo, File> iter(renamedFrom);
    while (iter.hasNext())
    {
        iter.next();
        const UniqueInfo info = iter.key();
        if (renamedTo.contains(info))
        {
            eventRenamed(iter.value(), renamedTo.value(info));
            renamedTo.remove(info);
        }
        else
        {
            eventRemoved(iter.value());
        }
    }

    iter = QHashIterator<UniqueInfo, File>(renamedTo);
    while (iter.hasNext())
    {
        iter.next();
        eventAdded(iter.value());
    }
}

UniqueInfo FileSystem::uniqueInfo(const File &file)
{
    UniqueInfo unique;

    HANDLE handle = CreateFileW(
        reinterpret_cast<const wchar_t *>(file.constData()),
        GENERIC_READ,
        FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (handle == INVALID_HANDLE_VALUE)
    {
        log("FileSystem: Cannot open file %1", file);
        return unique;
    }

    BY_HANDLE_FILE_INFORMATION info;
    if (!GetFileInformationByHandle(handle, &info))
    {
        log("FileSystem: Cannot get file information %1", file);
        return unique;
    }

    unique.volume = info.dwVolumeSerialNumber;
    unique.low = info.nFileIndexLow;
    unique.high = info.nFileIndexHigh;

    if (!CloseHandle(handle))
        log("FileSystem: Cannot close handle %1", file);

    return unique;
}
