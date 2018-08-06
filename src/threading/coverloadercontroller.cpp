#include "coverloadercontroller.hpp"

CoverLoaderController::CoverLoaderController(QObject *parent)
    : CoverLoaderController(AudioVector(), parent)
{

}

CoverLoaderController::CoverLoaderController(AudioVector audios, QObject *parent)
    : AbstractController(parent)
    , m_audios(audios)
{

}

CoverLoaderController::~CoverLoaderController()
{

}

void CoverLoaderController::setAudios(const AudioVector &audios)
{
    m_audios = audios;
}

AudioVector CoverLoaderController::audios() const
{
    return m_audios;
}

void CoverLoaderController::start()
{
    for (AudioVector chunk : chunk<Audio *>(m_audios, QThread::idealThreadCount()))
    {
        CoverLoaderWorker *worker = new CoverLoaderWorker(chunk);
        QThread *thread = createWorkerThread(worker);
        thread->start();
    }
}
