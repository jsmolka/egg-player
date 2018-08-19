#ifndef AUDIOUPDATERWORKER_HPP
#define AUDIOUPDATERWORKER_HPP

#include "abstractworker.hpp"
#include "audio.hpp"

class AudioUpdaterWorker : public AbstractWorker
{
    Q_OBJECT

public:
    explicit AudioUpdaterWorker(QObject *parent = nullptr);
    explicit AudioUpdaterWorker(Audio *audio, QObject *parent = nullptr);
    ~AudioUpdaterWorker();

    void setAudio(Audio *audio);
    Audio *audio() const;

public slots:
    void work() override;

private:
    Audio *m_audio;
};

#endif // AUDIOUPDATERWORKER_HPP
