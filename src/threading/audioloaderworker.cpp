#include "audioloaderworker.hpp"

AudioLoaderWorker::AudioLoaderWorker(QObject *parent)
    : AudioLoaderWorker(Files(), parent)
{

}

AudioLoaderWorker::AudioLoaderWorker(const Files &files, QObject *parent)
    : AbstractThread(parent)
    , m_files(files)
{

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
        if (isInterrupt())
            return;

        Audio *audio = cache.load(file);

        if (!audio)
            audio = new Audio(file);

        if (audio->isValid())
            emit loaded(audio);
        else
            delete audio;
    }
}
