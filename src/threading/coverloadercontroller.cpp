#include "coverloadercontroller.hpp"

#include "cache.hpp"
#include "coverloaderworker.hpp"

CoverLoaderController::CoverLoaderController(QObject *parent)
    : CoverLoaderController(Audio::vector(), parent)
{

}

CoverLoaderController::CoverLoaderController(Audio::vector audios, QObject *parent)
    : AbstractController(parent)
    , m_audios(audios)
{

}

CoverLoaderController::~CoverLoaderController()
{

}

void CoverLoaderController::setAudios(const Audio::vector &audios)
{
    m_audios = audios;
}

Audio::vector CoverLoaderController::audios() const
{
    return m_audios;
}

void CoverLoaderController::start()
{
    for (const Audio::vector chunk : chunk<Audio *>(m_audios, QThread::idealThreadCount()))
    {
        CoverLoaderWorker *worker = new CoverLoaderWorker(chunk);
        QThread *thread = createWorkerThread(worker);
        thread->start();
    }
}
