#include "audioupdater.hpp"

#include <QMutex>
#include <QMutexLocker>

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

    static QMutex mutex;
    const QMutexLocker locker(&mutex);

    const int id = m_cache.insertCover(cover);
    if (id > 0)
        m_cache.setAudioCoverId(audio, id);
}
