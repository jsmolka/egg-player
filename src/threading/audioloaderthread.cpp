#include "audioloaderthread.hpp"

AudioLoaderThread::AudioLoaderThread(QObject *parent)
    : AbstractThread(parent)
    , m_pool(this)
{

}

AudioLoaderThread::~AudioLoaderThread()
{

}

void AudioLoaderThread::setFiles(const QVector<QString> &files)
{
    m_files = files;
}

QVector<QString> AudioLoaderThread::files() const
{
    return m_files;
}

void AudioLoaderThread::run()
{
    for (QVector<QString> chunk : Util::chunk<QString>(m_files, ThreadPool::advisedCount()))
    {
        AudioLoaderWorker *worker = new AudioLoaderWorker;
        worker->setFiles(chunk);
        connect(worker, SIGNAL(loaded(Audio *, bool)), this, SLOT(onWorkerLoaded(Audio *, bool)));
        m_pool.add(worker);
    }
    m_pool.start();

    while (m_pool.isRunning() && !isAbort())
        qApp->processEvents();
}

void AudioLoaderThread::onWorkerLoaded(Audio *audio, bool cached)
{
    if (!cached)
        m_cache.insertAudio(audio);

    if (audio->isOutdated())
        m_cache.updateAudio(audio);

    emit loaded(audio);
}
