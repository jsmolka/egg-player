#ifndef AUDIOS_STATE_HPP
#define AUDIOS_STATE_HPP

#include "core/audios/staticvector.hpp"

namespace audios
{

class State : public StaticVector
{
    Q_OBJECT

public:
    explicit State(const Audio::vector &vector, StaticVector *parent);

private slots:
    void removeAudio(Audio *audio);
};

}

#endif // AUDIOS_STATE_HPP
