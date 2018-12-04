#ifndef AUDIOS_CURRENTSTATE_HPP
#define AUDIOS_CURRENTSTATE_HPP

#include "core/audios/frozenvector.hpp"

namespace audios
{

class CurrentState : public FrozenVector
{
    Q_OBJECT

public:
    explicit CurrentState(const Audio::vector &vector, FrozenVector *parent);

private slots:
    void removeAudio(const Audio &audio);
};

}

#endif // AUDIOS_CURRENTSTATE_HPP
