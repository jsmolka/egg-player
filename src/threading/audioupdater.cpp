#include "audioupdater.hpp"

AudioUpdater::AudioUpdater(QObject *parent)
    : Callable(parent)
{

}

void AudioUpdater::update(Audio *audio)
{
    audio->update();
    audio->cover().invalidate();
    m_dbAudio.loadFrom(audio);
    m_dbAudio.commit();

    if (isInterrupted())
        return;

    const QPixmap cover = Cover::loadFromFile(audio->file());
    if (m_dbCover.getOrInsertCover(cover))

    m_dbAudio.setCoverId(m_dbCover.id());
    m_dbAudio.commit();
    audio->cover().setId(m_dbCover.id());

    emit updated(audio);
}
