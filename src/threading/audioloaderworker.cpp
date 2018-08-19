#include "audioloaderworker.hpp"

#include <QMutex>
#include <QMutexLocker>

#include "cache.hpp"
#include "types.hpp"

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
    for (const File &file : m_files)
    {
        if (isInterrupted())
            return;

        Audio *audio = cache.loadAudio(file);
        if (!audio)
            audio = new Audio(file);

        if (audio->isValid())
        {
            if (!audio->isCached())
            {
                m_uncached << audio;
            }
            if (audio->isOutdated())
            {
                audio->update();
                audio->cover().setId(0);
                m_outdated << audio;
            }
            emit loaded(audio);
        }
        else
        {
            delete audio;
        }
    }

    for (Audio *audio : m_uncached)
    {
        if (isInterrupted())
            return;

        static QMutex mutex;
        const QMutexLocker locker(&mutex);

        cache.insertAudio(audio);
    }

    for (Audio *audio : m_outdated)
    {
        if (isInterrupted())
            return;

        cache.updateAudio(audio);
    }

    emit finished();
}
