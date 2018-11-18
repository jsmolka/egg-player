#include "directory.hpp"

#include <QDirIterator>

#include "core/utils.hpp"

fs::Directory::Directory(const QString &path, QObject *parent)
    : QObject(parent)
    , m_addPolicy(AddPolicy::Process)
    , m_path(path)
{

}

QString fs::Directory::path() const
{
    return m_path;
}

QSet<QString> fs::Directory::files() const
{
    return m_files;
}

QHash<QString, fs::Directory *> fs::Directory::subdirs() const
{
    return m_subdirs;
}

bool fs::Directory::exists() const
{
    return QDir(m_path).exists();
}

void fs::Directory::init()
{
    QDirIterator iter(m_path, QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    while (iter.hasNext())
    {
        const QString file = iter.next();
        const QFileInfo info = iter.fileInfo();

        if (info.isFile())
        {
            if (Util::isAudioFile(file))
                m_files << file;
        }
        if (info.isDir())
        {
            Directory *dir = new Directory(file, this);
            dir->init();

            m_subdirs.insert(file, dir);
        }
    }
}

QStrings fs::Directory::update()
{
    QStrings changes;

    processRemovedDirChanges(changes);
    processExistingDirChanges(changes);
    processFileChanges(changes);

    return changes;
}

QStrings fs::Directory::deleteRecursive(fs::Directory *dir)
{
    QStrings files;

    for (Directory *subdir : dir->subdirs())
    {
        files << deleteRecursive(subdir);
        emit removed(subdir);
    }

    for (const QString &file : dir->files())
        files << file;

    return files;
}

void fs::Directory::processRemovedDirChanges(QStrings &changes)
{
    for (auto iter = m_subdirs.begin(); iter != m_subdirs.end(); )
    {
        if (!(*iter)->exists())
        {
            changes << deleteRecursive(*iter);

            emit removed(*iter);
            iter = m_subdirs.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}

void fs::Directory::processExistingDirChanges(QStrings &changes)
{
    QDirIterator iter(m_path, QDir::Dirs | QDir::NoDotAndDotDot);
    while (iter.hasNext())
    {
        const QString path = iter.next();
        Directory *dir = m_subdirs.value(path, nullptr);
        if (!dir)
        {
            if (m_addPolicy == AddPolicy::Process)
            {
                dir = new Directory(path, this);

                m_subdirs.insert(path, dir);
                emit added(dir);
            }
        }
        if (m_addPolicy == AddPolicy::Process)
            changes << dir->update();
    }
}

void fs::Directory::processFileChanges(QStrings &changes)
{
    if (!exists())
    {
        for (const QString &file : m_files)
            changes << file;
        emit removed(this);
        return;
    }

    for (auto iter = m_files.begin(); iter != m_files.end(); )
    {
        if (!QFileInfo::exists(*iter))
        {
            changes << *iter;
            iter = m_files.erase(iter);
        }
        else
        {
            ++iter;
        }
    }

    QDirIterator iter(m_path, QStringList() << "*.mp3", QDir::Files);
    while (iter.hasNext())
    {
        const QString file = iter.next();
        if (!m_files.contains(file))
        {
            changes << file;
            m_files.insert(file);
        }
    }
}
