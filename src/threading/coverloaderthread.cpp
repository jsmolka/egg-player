#include "coverloaderthread.hpp"

CoverLoaderThread::CoverLoaderThread(QObject *parent)
    : AbstractThread(parent)
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
    for (Audios chunk : Util::chunk<Audio *>(m_audios, ThreadPool::advisedCount()))
    {
        CoverLoaderWorker *worker = new CoverLoaderWorker;
        worker->setAudios(chunk);
        connect(worker, SIGNAL(loaded(Audio *, QPixmap)), this, SLOT(onWorkerLoaded(Audio *, QPixmap)));
        m_pool.add(worker);
    }
    m_pool.start();

    while (m_pool.isRunning() && !isAbort())
        qApp->processEvents();
}

void CoverLoaderThread::onWorkerLoaded(Audio *audio, QPixmap cover)
{
    int id = m_cache.insertCover(cover);
    if (id != -1)
        m_cache.setAudioCoverId(audio, id);
}
