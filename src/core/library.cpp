#include "library.hpp"

#include <QDir>

#include "core/logger.hpp"
#include "core/macros.hpp"

Library::Library(QObject *parent)
    : QObject(parent)
    , m_audios(this)
    , m_audioLoader(this)
    , m_coverLoader(this)
{
    connect(&m_audioLoader, &AudioLoader::loaded, this, &Library::insert);
    connect(&m_audioLoader, &AudioLoader::finished, this, &Library::onAudioLoaderFinished);
    connect(&m_audioUpdater, &AudioUpdater::updated, this, &Library::onAudioUpdaterUpdated);

    connect(&m_fileSystem, &FileSystem::added, this, &Library::load);
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

void Library::init(const QStrings &paths)
{
    for (const QString &path : paths)
    {
        if (QDir(path).exists())
            m_fileSystem.addPath(path);
        else
            egg_log() << "Library path does not exist" << path;
    }
    load(m_fileSystem.globFiles());
}

void Library::insert(Audio *audio)
{
    m_fileSystem.watchAudio(audio);

    m_audios.insert(m_audios.lowerBound(audio), audio);
}

void Library::load(const QStrings &files)
{
    m_audioLoader.setFiles(files);
    m_audioLoader.start();
}

void Library::onAudioLoaderFinished()
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

void Library::onFileSystemRenamed(Audio *audio, const QString &name)
{
    audio->setFile(name);
}

void Library::onFileSystemRemoved(Audio *audio)
{
    m_audios.removeAudio(audio);
}
