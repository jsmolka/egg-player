#include "audioupdater.hpp"

AudioUpdater::AudioUpdater(QObject *parent)
    : Callable(parent)
{

}

void AudioUpdater::update(Audio *audio)
{
    audio->cover().setId(0);
    audio->update();
    m_cache.updateAudio(audio);

    if (isInterrupted())
        return;

    const QPixmap cover = Cover::loadFromFile(audio->wideFile());
    m_cache.updateAudioCover(audio, cover);
}
