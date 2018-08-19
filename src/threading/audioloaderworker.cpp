#include "audioloaderworker.hpp"

#include <QMutex>
#include <QMutexLocker>

#include "cache.hpp"
#include "types.hpp"

AudioLoaderWorker::AudioLoaderWorker(QObject *parent)
    : AudioLoaderWorker(Paths(), parent)
{

}

AudioLoaderWorker::AudioLoaderWorker(const Paths &paths, QObject *parent)
    : AbstractWorker(parent)
    , m_paths(paths)
{

}

AudioLoaderWorker::~AudioLoaderWorker()
{

}

void AudioLoaderWorker::setPaths(const Paths &paths)
{
    m_paths = paths;
}

Files AudioLoaderWorker::paths() const
{
    return m_paths;
}

void AudioLoaderWorker::work()
{
    Cache cache;
    for (const QString &path : m_paths)
    {
        if (isInterrupted())
            return;

        Audio *audio = cache.loadAudio(path);
        if (!audio)
            audio = new Audio(path);

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
