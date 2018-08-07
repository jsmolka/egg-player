#include "audioupdaterworker.hpp"

AudioUpdaterWorker::AudioUpdaterWorker(QObject *parent)
    : AudioUpdaterWorker(nullptr, parent)
{

}

AudioUpdaterWorker::AudioUpdaterWorker(Audio *audio, QObject *parent)
    : AbstractWorker(parent)
    , m_audio(audio)
{

}

AudioUpdaterWorker::~AudioUpdaterWorker()
{

}

void AudioUpdaterWorker::setAudio(Audio *audio)
{
    m_audio = audio;
}

Audio * AudioUpdaterWorker::audio() const
{
    return m_audio;
}

void AudioUpdaterWorker::work()
{
    Cache cache;
    m_audio->cover()->setId(0);
    m_audio->update();
    cache.updateAudio(m_audio);

    if (isInterrupted())
        return;

    QPixmap cover = Cover::loadFromFile(m_audio->widePath());

    static QMutex mutex;
    QMutexLocker locker(&mutex);

    int id = cache.insertCover(cover);
    if (id != 0)
        cache.setAudioCoverId(m_audio, id);
}
