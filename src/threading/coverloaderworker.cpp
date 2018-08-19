#include "coverloaderworker.hpp"

CoverLoaderWorker::CoverLoaderWorker(QObject *parent)
    : CoverLoaderWorker(AudioVector(), parent)
{

}

CoverLoaderWorker::CoverLoaderWorker(const AudioVector &audios, QObject *parent)
    : AbstractWorker(parent)
    , m_audios(audios)
{

}

CoverLoaderWorker::~CoverLoaderWorker()
{

}

void CoverLoaderWorker::setAudios(const AudioVector &audios)
{
    m_audios = audios;
}

AudioVector CoverLoaderWorker::audios() const
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

        if (!audio->cover().isValid())
        {
            QPixmap cover = Cover::loadFromFile(audio->widePath());

            static QMutex mutex;
            QMutexLocker locker(&mutex);

            int id = cache.insertCover(cover);
            if (id != 0)
                cache.setAudioCoverId(audio, id);
        }
    }
    emit finished();
}
