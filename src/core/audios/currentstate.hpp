#ifndef AUDIOS_CURRENTSTATE_HPP
#define AUDIOS_CURRENTSTATE_HPP

#include <QVector>

#include "core/audio.hpp"
#include "core/audios/audiosbase.hpp"

namespace audios
{

class CurrentState : public AudiosBase
{
    Q_OBJECT

public:
    CurrentState(const QVector<Audio> &vector, AudiosBase *parent);

private slots:
    void removeAudio(const Audio &audio);
};

}

#endif // AUDIOS_CURRENTSTATE_HPP
