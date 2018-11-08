#include "audioloader.hpp"

#include "core/database/cache.hpp"

void AudioLoader::load(const QString &file)
{
    Audio *audio = Cache::loadAudio(file);
    if (!audio)
        return;

    if (!insertAudio(audio))
        return;

    if (!updateAudio(audio))
        return;

    if (!loadCover(audio))
        return;

    emit loaded(audio);
}

bool AudioLoader::insertAudio(Audio *audio) const
{
    if (isInterrupted())
        return false;

    if (audio->isCached())
        return true;

    return Cache::insertAudio(audio);
}

bool AudioLoader::updateAudio(Audio *audio) const
{
    if (isInterrupted())
        return false;

    if (!audio->isOutdated())
        return true;

    if (!audio->read())
        return false;

    audio->cover().invalidate();
    return Cache::updateAudio(audio);
}

bool AudioLoader::loadCover(Audio *audio) const
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
