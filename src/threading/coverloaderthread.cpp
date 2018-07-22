#include "coverloaderthread.hpp"

CoverLoaderThread::CoverLoaderThread(QObject *parent)
    : CoverLoaderThread(Audios(), parent)
{

}

CoverLoaderThread::CoverLoaderThread(const Audios &audios, QObject *parent)
    : AbstractThread(parent)
    , m_audios(audios)
{

}

CoverLoaderThread::~CoverLoaderThread()
{

}

void CoverLoaderThread::setAudios(const Audios &audios)
{
    m_audios = audios;
}

Audios CoverLoaderThread::audios() const
{
    return m_audios;
}

void CoverLoaderThread::run()
{
    startWorkerThreads();

    while (m_pool.isRunning())
    {
        if (isAbort())
            return;

        msleep(100);
    }

    Cache cache;
    for (int i = 0; i < m_uncachedAudios.size(); ++i)
    {
        if (isAbort())
            return;

        int id = cache.insertCover(m_uncachedCover[i]);
        if (id != -1)
            cache.setAudioCoverId(m_uncachedAudios[i], id);
    }
}

void CoverLoaderThread::onWorkerLoaded(Audio *audio, QPixmap cover)
{
    m_uncachedAudios << audio;
    m_uncachedCover << cover;
}

void CoverLoaderThread::startWorkerThreads()
{
    for (Audios chunk : Util::chunk<Audio *>(m_audios, ThreadPool::advisedCount()))
    {
        CoverLoaderWorker *worker = new CoverLoaderWorker(chunk);
        connect(worker, SIGNAL(loaded(Audio *, QPixmap)), this, SLOT(onWorkerLoaded(Audio *, QPixmap)));
        m_pool.add(worker);
    }

    m_pool.start();
}
