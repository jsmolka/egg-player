#include "coverloaderworker.hpp"

#include "core/database/cache.hpp"

CoverLoaderWorker::CoverLoaderWorker(QObject *parent)
    : CoverLoaderWorker(Audio::vector(), parent)
{

}

CoverLoaderWorker::CoverLoaderWorker(const Audio::vector &audios, QObject *parent)
    : Runnable(parent)
    , m_audios(audios)
{

}

void CoverLoaderWorker::work()
{
    for (Audio *audio : qAsConst(m_audios))
    {
        if (!loadCover(audio))
            return;
    }
    emit finished();
}

bool CoverLoaderWorker::loadCover(Audio *audio)
{
    if (isInterrupted())
        return false;

    if (!audio->cover().isValid())
    {
        const QPixmap cover = Cover::loadFromFile(audio->file());
        if (!cover.isNull())
            Cache::updateAudioCover(audio, cover);
    }
    return true;
}
