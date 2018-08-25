#include "coverloaderworker.hpp"

#include <QMutex>
#include <QMutexLocker>

#include "cache.hpp"

CoverLoaderWorker::CoverLoaderWorker(QObject *parent)
    : CoverLoaderWorker(Audio::vector(), parent)
{

}

CoverLoaderWorker::CoverLoaderWorker(const Audio::vector &audios, QObject *parent)
    : AbstractWorker(parent)
    , m_audios(audios)
{

}

void CoverLoaderWorker::setAudios(const Audio::vector &audios)
{
    m_audios = audios;
}

Audio::vector CoverLoaderWorker::audios() const
{
    return m_audios;
}

void CoverLoaderWorker::work()
{
    Cache cache;
    for (Audio *audio : qAsConst(m_audios))
    {
        if (isInterrupted())
            return;

        if (!audio->cover().isValid())
        {
            const QPixmap cover = Cover::loadFromFile(audio->wideFile());

            static QMutex mutex;
            const QMutexLocker locker(&mutex);

            const int id = cache.insertCover(cover);
            if (id > 0)
                cache.setAudioCoverId(audio, id);
        }
    }
    emit finished();
}
