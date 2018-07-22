#include "audioloaderworker.hpp"

AudioLoaderWorker::AudioLoaderWorker(QObject *parent)
    : AbstractThread(parent)
{
    m_buffer.reserve(25);
}

AudioLoaderWorker::AudioLoaderWorker(const Files &files, QObject *parent)
    : AbstractThread(parent)
    , m_files(files)
{
    m_buffer.reserve(25);
}

AudioLoaderWorker::~AudioLoaderWorker()
{

}

void AudioLoaderWorker::setFiles(const Files &files)
{
    m_files = files;
}

Files AudioLoaderWorker::files() const
{
    return m_files;
}

void AudioLoaderWorker::run()
{
    Cache cache;
    for (const QString &file : m_files)
    {
        if (isAbort())
            return;

        Audio *audio = cache.load(file);

        if (!audio)
            audio = new Audio(file);

        if (audio->isValid())
            fillBuffer(audio);
        else
            delete audio;
    }

    emit loaded(m_buffer);
}

void AudioLoaderWorker::fillBuffer(Audio *audio)
{
    m_buffer << audio;

    if (m_buffer.size() == 25)
    {
        emit loaded(m_buffer);

        m_buffer.clear();
        m_buffer.reserve(25);
    }
}
