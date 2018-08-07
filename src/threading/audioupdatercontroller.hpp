#ifndef AUDIOUPDATERCONTROLLER_HPP
#define AUDIOUPDATERCONTROLLER_HPP

#include "abstractcontroller.hpp"
#include "audioupdaterworker.hpp"
#include "audio.hpp"

class AudioUpdaterController : public AbstractController
{
    Q_OBJECT

public:
    AudioUpdaterController(QObject *parent = nullptr);
    AudioUpdaterController(Audio *audio, QObject *parent = nullptr);
    ~AudioUpdaterController();

    void setAudio(Audio *audio);
    Audio * audio() const;

public slots:
    void start() override;

private:
    Audio *m_audio;
};

#endif // AUDIOUPDATERCONTROLLER_HPP
