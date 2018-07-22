#include "audioloaderthread.hpp"

AudioLoaderThread::AudioLoaderThread(QObject *parent)
    : AbstractThread(parent)
    , m_pool(this)
{
    m_buffer.reserve(100);
}

AudioLoaderThread::AudioLoaderThread(const Files &files, QObject *parent)
    : AbstractThread(parent)
    , m_files(files)
    , m_pool(this)
{
    m_buffer.reserve(100);
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
    for (Files chunk : Util::chunk<QString>(m_files, 4))
    {
        AudioLoaderWorker *worker = new AudioLoaderWorker(chunk);
        connect(worker, SIGNAL(loaded(Audios)), this, SLOT(onWorkerLoaded(Audios)));
        m_pool.add(worker);
    }
    m_pool.start();

    while (m_pool.isRunning() && !isAbort())
        msleep(200);

    emit loaded(m_buffer);
}

void AudioLoaderThread::onWorkerLoaded(Audios audios)
{
    for (Audio *audio : audios)
    {
        if (!audio->isCached())
            m_cache.insertAudio(audio);
    }

    fillBuffer(audios);
}

void AudioLoaderThread::fillBuffer(Audios audios)
{
    m_buffer << audios;

    if (m_buffer.size() >= 100)
    {
        emit loaded(m_buffer);

        m_buffer.clear();
        m_buffer.reserve(100);
    }
}
