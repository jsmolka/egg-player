#include "audioloaderworker.hpp"

#include "core/cache.hpp"

AudioLoaderWorker::AudioLoaderWorker(const QStrings &files)
    : m_files(files)
{

}

void AudioLoaderWorker::work()
{
    for (const QString &file : m_files)
    {
        Audio audio = Cache::loadAudio(file);
        if (!audio.isValid())
            continue;

        if (!insertAudio(audio))
            return;

        if (!updateAudio(audio))
            return;

        emit loaded(audio);
    }
    emit finished();
}

bool AudioLoaderWorker::insertAudio(Audio &audio) const
{
    if (isInterrupted())
        return false;

    if (audio.isCached())
        return true;

    return Cache::insertAudio(audio);
}

bool AudioLoaderWorker::updateAudio(Audio &audio) const
{
    if (isInterrupted())
        return false;

    if (!audio.isOutdated())
        return true;

    if (!audio.read())
        return false;

    audio.cover().invalidate();
    return Cache::updateAudio(audio);
}
