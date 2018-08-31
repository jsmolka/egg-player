#include "library.hpp"

#include <QApplication>

Library::Library(QObject *parent)
    : Library(false, parent)
{

}

Library::Library(bool sorted, QObject *parent)
    : QObject(parent)
    , m_sorted(sorted)
    , m_audios(this)
    , m_initialLoader(this)
    , m_coverLoader(this)
{
    connect(&m_initialLoader, &InitialLoader::loaded, this, &Library::insert);
    connect(&m_initialLoader, &InitialLoader::finished,this, &Library::onAudioLoaderFinished);

    connect(&m_fileSystem, &FileSystem::modified, &m_audioUpdater, &AudioUpdater::update);
    connect(&m_fileSystem, &FileSystem::renamed, this, &Library::onFileSystemRenamed);
    connect(&m_fileSystem, &FileSystem::added, &m_audioLoader, &AudioLoader::load);
    connect(&m_audioLoader, &AudioLoader::loaded, this, &Library::insert);
    connect(&m_fileSystem, &FileSystem::removed, this, &Library::onFileSystemRemoved);
}

Library *Library::instance()
{
    static Library *library = new Library(qApp);
    return library;
}

void Library::setSorted(bool sorted)
{
    m_sorted = sorted;
}

bool Library::isSorted() const
{
    return m_sorted;
}

Audios *Library::audios()
{
    return &m_audios;
}

void Library::initialLoad(const Paths &paths)
{
    for (const Path &path : paths)
        m_fileSystem.addPath(path);

    m_initialLoader.setFiles(m_fileSystem.globAudios());
    m_initialLoader.start();
}

void Library::insert(Audio *audio)
{
    audio->setParent(this);
    m_fileSystem.watchAudio(audio);

    if (m_sorted)
        m_audios.insert(lowerBound(audio), audio);
    else
        m_audios.append(audio);
}

void Library::onAudioLoaderFinished()
{
    m_coverLoader.setAudios(m_audios.vector());
    m_coverLoader.start();
}

void Library::onFileSystemRenamed(Audio *audio, const File &to)
{
    audio->setFile(to);
}

void Library::onFileSystemRemoved(Audio *audio)
{
    m_audios.remove(audio);
    audio->deleteLater();
}

int Library::lowerBound(Audio *audio)
{
    int low = 0;
    int high = m_audios.size();
    while (low < high)
    {
        const int mid = (low + high) / 2;
        if (*audio < *m_audios.at(mid))
            high = mid;
        else
            low = mid + 1;
    }
    return low;
}
