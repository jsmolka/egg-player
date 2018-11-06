#include "library.hpp"

#include "core/macros.hpp"

Library::Library(QObject *parent)
    : QObject(parent)
    , m_audios(this)
    , m_initialLoader(this)
    , m_coverLoader(this)
{
    connect(&m_initialLoader, &InitialLoader::loaded, this, &Library::insert);
    connect(&m_initialLoader, &InitialLoader::finished, this, &Library::onInitialLoaderFinished);
    connect(&m_audioLoader, &AudioLoader::loaded, this, &Library::insert);
    connect(&m_audioUpdater, &AudioUpdater::updated, this, &Library::onAudioUpdaterUpdated);

    connect(&m_fileSystem, &FileSystem::added, &m_audioLoader, &AudioLoader::load);
    connect(&m_fileSystem, &FileSystem::renamed, this, &Library::onFileSystemRenamed);
    connect(&m_fileSystem, &FileSystem::removed, this, &Library::onFileSystemRemoved);
    connect(&m_fileSystem, &FileSystem::modified, &m_audioUpdater, &AudioUpdater::update);
}

const Audios &Library::audios() const
{
    return m_audios;
}

const FileSystem &Library::fileSystem() const
{
    return m_fileSystem;
}

Audios &Library::audios()
{
    return EGG_REF_CAST(Library, Audios, audios);
}

FileSystem &Library::fileSystem()
{
    return EGG_REF_CAST(Library, FileSystem, fileSystem);
}

void Library::initialLoad(const QStrings &paths)
{
    for (const QString &path : paths)
        m_fileSystem.addPath(path);

    m_initialLoader.setFiles(m_fileSystem.globFiles());
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

    m_audios.insert(m_audios.lowerBound(audio), audio);
}

void Library::onInitialLoaderFinished()
{
    m_coverLoader.setAudios(m_audios.vector());
    m_coverLoader.start();
}

void Library::onAudioUpdaterUpdated(Audio *audio)
{
    const int index = m_audios.indexOf(audio);
    if (index == m_audios.lowerBound(audio))
    {
        emit m_audios.updated(index);
    }
    else
    {
        m_audios.remove(index);
        m_audios.insert(m_audios.lowerBound(audio), audio);
    }
}

void Library::onFileSystemRenamed(Audio *audio, const QString &file)
{
    audio->setFile(file);
}

void Library::onFileSystemRemoved(Audio *audio)
{
    m_audios.removeAudio(audio);
}
