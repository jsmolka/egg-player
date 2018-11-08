#include "audioupdater.hpp"

#include "core/database/cache.hpp"

void AudioUpdater::update(Audio *audio)
{
    if (!updateAudio(audio))
        return;

    if (!loadCover(audio))
        return;

    emit updated(audio);
}

bool AudioUpdater::updateAudio(Audio *audio) const
{
    if (isInterrupted())
        return false;

    if (!audio->read())
        return false;

    audio->cover().invalidate();
    return Cache::updateAudio(audio);
}

bool AudioUpdater::loadCover(Audio *audio) const
{
    if (isInterrupted())
        return false;

    const QPixmap cover = Cover::loadFromFile(audio->file());
    if (cover.isNull())
        return false;

    return Cache::updateAudioCover(audio, cover);
}
