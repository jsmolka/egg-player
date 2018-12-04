#include "coverloader.hpp"

#include "threading/coverloaderworker.hpp"

void CoverLoader::start()
{
#ifdef QT_DEBUG
    const int threads = 1;
#else
    const int threads = QThread::idealThreadCount();
#endif

    for (const Audio::vector &chunk : chunk<Audio>(m_audios, threads))
    {
        auto *worker = new CoverLoaderWorker(chunk);
        runWorker(worker);
    }
}
