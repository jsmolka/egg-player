#include "audioupdatercontroller.hpp"

#include "audioupdaterworker.hpp"

AudioUpdaterController::AudioUpdaterController(QObject *parent)
    : AudioUpdaterController(nullptr, parent)
{

}

AudioUpdaterController::AudioUpdaterController(Audio *audio, QObject *parent)
    : AbstractController(parent)
    , m_audio(audio)
{

}

void AudioUpdaterController::setAudio(Audio *audio)
{
    m_audio = audio;
}

Audio *AudioUpdaterController::audio() const
{
    return m_audio;
}

void AudioUpdaterController::start()
{
    AudioUpdaterWorker *worker = new AudioUpdaterWorker(m_audio);
    QThread *thread = createWorkerThread(worker);
    thread->start();
}
