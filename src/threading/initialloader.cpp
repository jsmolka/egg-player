#include "initialloader.hpp"

#include "threading/initialloaderworker.hpp"

void InitialLoader::start()
{
#ifdef QT_DEBUG
    const int threads = 1;
#else
    const int threads = QThread::idealThreadCount();
#endif

    for (const QStrings &chunk : chunk<QString>(m_files, threads))
    {
        InitialLoaderWorker *worker = new InitialLoaderWorker(chunk);
        connect(worker, &InitialLoaderWorker::loaded, this, &InitialLoader::loaded);
        runWorker(worker);
    }
}
