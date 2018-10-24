#include "audioupdater.hpp"

#include "cache.hpp"

AudioUpdater::AudioUpdater(QObject *parent)
    : Callable(parent)
{

}

void AudioUpdater::update(Audio *audio)
{
    audio->update();
    audio->cover().invalidate();
    Cache::updateAudio(audio);

    if (isInterrupted())
        return;

    const QPixmap cover = Cover::loadFromFile(audio->file());
    if (!cover.isNull())
        Cache::updateAudioCover(audio, cover);

    emit updated(audio);
}
