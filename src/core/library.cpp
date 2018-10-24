#include "library.hpp"

#include <QApplication>

Library::Library(QObject *parent)
    : QObject(parent)
    , m_audios(this)
    , m_initialLoader(this)
    , m_coverLoader(this)
{
    connect(&m_initialLoader, &InitialLoader::loaded, this, &Library::insert);
    connect(&m_initialLoader, &InitialLoader::finished,this, &Library::onInitialLoaderFinished);
    connect(&m_audioLoader, &AudioLoader::loaded, this, &Library::insert);
    connect(&m_audioUpdater, &AudioUpdater::updated, this, &Library::onAudioUpdaterUpdated);

    connect(&m_fileSystem, &FileSystem::added, &m_audioLoader, &AudioLoader::load);
    connect(&m_fileSystem, &FileSystem::renamed, this, &Library::onFileSystemRenamed);
    connect(&m_fileSystem, &FileSystem::removed, this, &Library::onFileSystemRemoved);
    connect(&m_fileSystem, &FileSystem::modified, &m_audioUpdater, &AudioUpdater::update);
}

Library *Library::instance()
{
    static Library *library = new Library(qApp);
    return library;
}

Audios *Library::audios()
{
    return &m_audios;
}

FileSystem &Library::fileSystem() const
{
    return const_cast<FileSystem &>(m_fileSystem);
}

void Library::initialLoad(const QStrings &paths)
{
    for (const QString &path : paths)
        m_fileSystem.addPath(path);

    m_initialLoader.setFiles(m_fileSystem.globAudios());
    m_initialLoader.start();
}

void Library::loadFiles(const QStrings &files)
{
    for (const QString &file : files)
    {
        if (!m_fileSystem.audios().contains(file))
            m_audioLoader.load(file);
    }
}

void Library::insert(Audio *audio)
{
    m_fileSystem.watchAudio(audio);
    m_audios.insert(lowerBound(audio), audio);
}

void Library::onInitialLoaderFinished()
{
    m_coverLoader.setAudios(m_audios.vector());
    m_coverLoader.start();
}

void Library::onAudioUpdaterUpdated(Audio *audio)
{
    const int low = lowerBound(audio);
    if (audio != m_audios.at(low))
    {
        const int index = m_audios.indexOf(audio);
        if (index != -1)
            m_audios.move(index, low);
    }
    else
    {
        emit m_audios.updated(low);
    }
}

void Library::onFileSystemRenamed(Audio *audio, const QString &to)
{
    audio->setFile(to);
}

void Library::onFileSystemRemoved(Audio *audio)
{
    m_audios.remove(audio);
}

int Library::lowerBound(Audio *audio)
{
    int low = 0;
    int high = m_audios.size();
    while (low < high)
    {
        const int mid = (low + high) / 2;
        const int diff = audio->tag().title().compare(m_audios.at(mid)->tag().title(), Qt::CaseInsensitive);
        if (diff <= 0)
            high = mid;
        else
            low = mid + 1;
    }
    return low;
}
