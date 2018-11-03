#include "coverloaderworker.hpp"

#include "core/database/cache.hpp"

CoverLoaderWorker::CoverLoaderWorker(const Audio::vector &audios)
    : m_audios(audios)
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

    if (audio->cover().isValid())
        return true;

    const QPixmap cover = Cover::loadFromFile(audio->file());
    if (cover.isNull())
        return false;

    return Cache::updateAudioCover(audio, cover);
}
