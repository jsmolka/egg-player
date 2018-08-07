#ifndef AUDIOUPDATERWORKER_HPP
#define AUDIOUPDATERWORKER_HPP

#include <QMutex>
#include <QMutexLocker>

#include "abstractworker.hpp"
#include "audio.hpp"
#include "cache.hpp"
#include "cover.hpp"

class AudioUpdaterWorker : public AbstractWorker
{
    Q_OBJECT

public:
    AudioUpdaterWorker(QObject *parent = nullptr);
    AudioUpdaterWorker(Audio *audio, QObject *parent = nullptr);
    ~AudioUpdaterWorker();

    void setAudio(Audio *audio);
    Audio * audio() const;

public slots:
    void work() override;

private:
    Audio *m_audio;
};

#endif // AUDIOUPDATERWORKER_HPP
