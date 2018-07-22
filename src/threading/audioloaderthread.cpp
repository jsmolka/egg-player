#include "audioloaderthread.hpp"

AudioLoaderThread::AudioLoaderThread(QObject *parent)
    : AudioLoaderThread(Files(), parent)
{

}

AudioLoaderThread::AudioLoaderThread(const Files &files, QObject *parent)
    : AbstractThread(parent)
    , m_files(files)
    , m_pool(this)
{

}

AudioLoaderThread::~AudioLoaderThread()
{

}

void AudioLoaderThread::setFiles(const Files &files)
{
    m_files = files;
}

Files AudioLoaderThread::files() const
{
    return m_files;
}

void AudioLoaderThread::run()
{
    startWorkerThreads();

    while (m_pool.isRunning())
    {
        if (isInterrupt())
            return;

        msleep(100);
    }

    Cache cache;
    for (Audio *audio : m_uncached)
    {
        if (isInterrupt())
            return;

        cache.insertAudio(audio);
    }
}

void AudioLoaderThread::onWorkerLoaded(Audio *audio)
{
    if (!audio->isCached())
        m_uncached << audio;

    emit loaded(audio);
}

void AudioLoaderThread::startWorkerThreads()
{
    for (Files chunk : Util::chunk<QString>(m_files, ThreadPool::idealCount()))
    {
        AudioLoaderWorker *worker = new AudioLoaderWorker(chunk);
        connect(worker, SIGNAL(loaded(Audio *)), this, SLOT(onWorkerLoaded(Audio *)));
        m_pool.add(worker);
    }

    m_pool.start();
}
