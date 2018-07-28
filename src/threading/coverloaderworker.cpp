#include "coverloaderworker.hpp"

CoverLoaderWorker::CoverLoaderWorker(QObject *parent)
    : CoverLoaderWorker(Audios(), parent)
{

}

CoverLoaderWorker::CoverLoaderWorker(const Audios &audios, QObject *parent)
    : AbstractWorker(parent)
    , m_audios(audios)
{

}

CoverLoaderWorker::~CoverLoaderWorker()
{

}

void CoverLoaderWorker::setAudios(const Audios &audios)
{
    m_audios = audios;
}

Audios CoverLoaderWorker::audios() const
{
    return m_audios;
}

void CoverLoaderWorker::work()
{
    Cache cache;
    for (Audio *audio : m_audios)
    {
        if (isInterrupted())
            return;

        if (audio->cover().id() == -1)
        {
            QPixmap cover = Cover::loadFromFile(audio->pathWChar());

            static QMutex mutex;
            QMutexLocker locker(&mutex);

            int id = cache.insertCover(cover);
            if (id != -1)
            {
                cache.setAudioCoverId(audio, id);
                audio->cover().setId(id);
            }
        }
    }
    emit finished();
}
