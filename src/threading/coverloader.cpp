#include "coverloader.hpp"

#include "threading/coverloaderworker.hpp"

void CoverLoader::start()
{
#ifdef QT_DEBUG
    const int threads = 1;
#else
    const int threads = QThread::idealThreadCount();
#endif

    for (const QVector<Audio> &chunk : chunk<Audio>(m_audios, threads))
    {
        CoverLoaderWorker *worker = new CoverLoaderWorker(chunk);
        runWorker(worker);
    }
}
