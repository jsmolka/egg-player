#ifndef AUDIOSSTATE_HPP
#define AUDIOSSTATE_HPP

#include "core/audios/audiosbase.hpp"

namespace audios
{
class State : public Base
{
    Q_OBJECT

public:
    explicit State(const Audio::vector &vector, Base *parent);

private slots:
    void removeAudio(Audio *audio);
};
}

#endif // AUDIOSSTATE_HPP
