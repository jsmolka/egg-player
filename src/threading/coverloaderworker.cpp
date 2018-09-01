#include "coverloaderworker.hpp"

#include "cache.hpp"

CoverLoaderWorker::CoverLoaderWorker(QObject *parent)
    : CoverLoaderWorker(Audio::vector(), parent)
{

}

CoverLoaderWorker::CoverLoaderWorker(const Audio::vector &audios, QObject *parent)
    : Runnable(parent)
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
            cache.updateAudioCover(audio, cover);
        }
    }
    emit finished();
}
