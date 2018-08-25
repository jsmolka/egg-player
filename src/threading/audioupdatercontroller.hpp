#ifndef AUDIOUPDATERCONTROLLER_HPP
#define AUDIOUPDATERCONTROLLER_HPP

#include "abstractcontroller.hpp"
#include "audio.hpp"

class AudioUpdaterController : public AbstractController
{
    Q_OBJECT

public:
    explicit AudioUpdaterController(QObject *parent = nullptr);
    explicit AudioUpdaterController(Audio *audio, QObject *parent = nullptr);

    void setAudio(Audio *audio);
    Audio *audio() const;

public slots:
    void start() override;

private:
    Audio *m_audio;
};

#endif // AUDIOUPDATERCONTROLLER_HPP
