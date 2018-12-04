#include "audioloader.hpp"

#include "threading/audioloaderworker.hpp"

void AudioLoader::start()
{
#ifdef QT_DEBUG
    const int threads = 1;
#else
    const int threads = QThread::idealThreadCount();
#endif

    for (const QStrings &chunk : chunk<QString>(m_files, threads))
    {
        auto *worker = new AudioLoaderWorker(chunk);
        connect(worker, &AudioLoaderWorker::loaded, this, &AudioLoader::loaded);
        runWorker(worker);
    }
}
