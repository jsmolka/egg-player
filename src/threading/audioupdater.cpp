#include "audioupdater.hpp"

AudioUpdater::AudioUpdater(QObject *parent)
    : Callable(parent)
{

}

void AudioUpdater::update(Audio *audio)
{
    audio->update();
    audio->cover().invalidate();
    m_cache.updateAudio(audio);

    if (isInterrupted())
        return;

    const QPixmap cover = Cover::loadFromFile(audio->file());
    m_cache.updateAudioCover(audio, cover);
}
