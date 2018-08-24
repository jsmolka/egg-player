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
    , m_fileSystem(this)
    , m_audioLoader(this)
    , m_audioUpdater(this)
    , m_coverLoader(this)
{
    connect(&m_audioLoader, &AudioLoaderController::loaded, this, &Library::insert);
    connect(&m_audioLoader, &AudioLoaderController::finished,this, &Library::onAudioLoaderFinished);

    connect(&m_fileSystem, &FileSystem::modified, this, &Library::onFileSystemModified);
    connect(&m_fileSystem, &FileSystem::renamed, this, &Library::onFileSystemRenamed);
    connect(&m_fileSystem, &FileSystem::added, this, &Library::onFileSystemAdded);
    connect(&m_fileSystem, &FileSystem::removed, this, &Library::onFileSystemRemoved);
}

Library::~Library()
{

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

AudioLoaderController &Library::audioLoader()
{
    return m_audioLoader;
}

AudioUpdaterController &Library::audioUpdater()
{
    return m_audioUpdater;
}

CoverLoaderController &Library::coverLoader()
{
    return m_coverLoader;
}

void Library::load(const Paths &paths)
{
    for (const Path &path : paths)
        m_fileSystem.addPath(path);

    m_audioLoader.setFiles(m_fileSystem.globAudios());
    m_audioLoader.start();
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

void Library::onFileSystemModified(Audio *audio)
{
    m_audioUpdater.setAudio(audio);
    m_audioUpdater.start();
}

void Library::onFileSystemRenamed(Audio *audio, const File &to)
{
    audio->setFile(to);
}

void Library::onFileSystemAdded(const File &file)
{
    m_audioLoader.setFiles(Files() << file);
    m_audioLoader.start();
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
