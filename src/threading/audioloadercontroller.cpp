#include "audioloadercontroller.hpp"

#include "audioloaderworker.hpp"

AudioLoaderController::AudioLoaderController(QObject *parent)
    : AudioLoaderController(Paths(), parent)
{

}

AudioLoaderController::AudioLoaderController(const Files &files, QObject *parent)
    : AbstractController(parent)
    , m_paths(files)
{

}

AudioLoaderController::~AudioLoaderController()
{

}

void AudioLoaderController::setPaths(const Paths &paths)
{
    m_paths = paths;
}

Paths AudioLoaderController::paths() const
{
    return m_paths;
}

void AudioLoaderController::start()
{
    for (const Paths chunk : chunk<Path>(m_paths, QThread::idealThreadCount()))
    {
        AudioLoaderWorker *worker = new AudioLoaderWorker(chunk);
        connect(worker, &AudioLoaderWorker::loaded, this, &AudioLoaderController::loaded);
        QThread *thread = createWorkerThread(worker);
        thread->start();
    }
}
