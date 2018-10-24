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

bool AudioUpdater::updateAudio(Audio *audio)
{
    if (isInterrupted())
        return false;

    if (!audio->update())
        return false;

    audio->cover().invalidate();
    Cache::updateAudio(audio);

    return true;
}

bool AudioUpdater::loadCover(Audio *audio)
{
    if (isInterrupted())
        return false;

    const QPixmap cover = Cover::loadFromFile(audio->file());
    if (!cover.isNull())
        Cache::updateAudioCover(audio, cover);

    return true;
}
