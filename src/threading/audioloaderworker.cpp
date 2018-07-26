#include "audioloaderworker.hpp"

AudioLoaderWorker::AudioLoaderWorker(QObject *parent)
    : AudioLoaderWorker(Files(), parent)
{

}

AudioLoaderWorker::AudioLoaderWorker(const Files &files, QObject *parent)
    : AbstractWorker(parent)
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

void AudioLoaderWorker::work()
{
    Cache cache;
    for (const QString &file : m_files)
    {
        if (isInterrupted())
            return;

        Audio *audio = cache.load(file);

        if (!audio)
        {
            audio = new Audio(file);
            if (audio->isValid())
                m_audios << audio;
        }

        if (audio->isValid())
            emit loaded(audio);
        else
            delete audio;
    }

    static QMutex mutex;
    QMutexLocker locker(&mutex);

    for (Audio *audio : m_audios)
    {
        if (isInterrupted())
            return;

        cache.insertAudio(audio);
    }

    emit finished();
}
