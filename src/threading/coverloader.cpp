#include "coverloader.hpp"

#include "coverloaderworker.hpp"

CoverLoader::CoverLoader(QObject *parent)
    : CoverLoader(Audio::vector(), parent)
{

}

CoverLoader::CoverLoader(Audio::vector audios, QObject *parent)
    : Controller(parent)
    , m_audios(audios)
{

}

void CoverLoader::setAudios(const Audio::vector &audios)
{
    m_audios = audios;
}

Audio::vector CoverLoader::audios() const
{
    return m_audios;
}

void CoverLoader::start()
{
#ifdef QT_DEBUG
    const int threads = 1;
#else
    const int threads = QThread::idealThreadCount();
#endif

    for (const Audio::vector &chunk : chunk<Audio *>(m_audios, threads))
    {
        CoverLoaderWorker *worker = new CoverLoaderWorker(chunk);
        runWorker(worker);
    }
}
