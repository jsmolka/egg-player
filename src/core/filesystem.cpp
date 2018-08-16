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
        result << iter.value()->files();
    }
    // Todo: Maybe reserve space here to const inserting time
    return result;
}

void FileSystem::eventModified(const File &file)
{
    qDebug() << "modified" << file;
}

void FileSystem::onDirParsed(Directory *dir)
{
    QStringList paths;
    for (const File &file : dir->files())
        paths << file;
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
    qDebug() << "changed dir" << dir;
}

UniqueInfo FileSystem::uniqueInfo(const File &file)
{
    UniqueInfo unique;

    HANDLE hFile = CreateFileW(
        reinterpret_cast<const wchar_t *>(file.constData()),
        GENERIC_READ,
        FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE)
    {
        log("FileSystem: Cannot open file %1", file);
        return unique;
    }

    BY_HANDLE_FILE_INFORMATION info;
    if (!GetFileInformationByHandle(hFile, &info))
    {
        log("FileSystem: Cannot get file information %1", file);
        return unique;
    }

    unique.volume = info.dwVolumeSerialNumber;
    unique.low = info.nFileIndexLow;
    unique.high = info.nFileIndexHigh;

    if (!CloseHandle(hFile))
        log("FileSystem: Cannot close handle %1", file);

    return unique;
}
