#include "audioloadercontroller.hpp"

AudioLoaderController::AudioLoaderController(QObject *parent)
    : AudioLoaderController(Files(), parent)
{

}

AudioLoaderController::AudioLoaderController(const Files &files, QObject *parent)
    : AbstractController(parent)
    , m_files(files)
{

}

AudioLoaderController::~AudioLoaderController()
{

}

void AudioLoaderController::setFiles(const Files &files)
{
    m_files = files;
}

Files AudioLoaderController::files() const
{
    return m_files;
}

void AudioLoaderController::start()
{
    for (Files chunk : Util::chunk<QString>(m_files, QThread::idealThreadCount()))
    {
        AudioLoaderWorker *worker = new AudioLoaderWorker(chunk);
        connect(worker, &AudioLoaderWorker::loaded, this, &AudioLoaderController::loaded);
        QThread *thread = createWorkerThread(worker);
        thread->start();
    }
}
