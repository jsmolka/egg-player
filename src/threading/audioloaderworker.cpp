#include "audioloaderworker.hpp"

AudioLoaderWorker::AudioLoaderWorker(QObject *parent)
    : AbstractThread(parent)
{

}

AudioLoaderWorker::~AudioLoaderWorker()
{

}

void AudioLoaderWorker::setFiles(const QVector<QString> &files)
{
    m_files = files;
}

QVector<QString> AudioLoaderWorker::files() const
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

        bool cached = true;
        Audio *audio = cache.load(file);

        if (!audio)
        {
            cached = false;
            audio = new Audio(file);
        }

        if (audio->isValid())
            emit loaded(audio, cached);
        else
            delete audio;
    }
}
