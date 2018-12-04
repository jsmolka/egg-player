#include "currentstate.hpp"

audios::CurrentState::CurrentState(const Audio::vector &vector, FrozenVector *parent)
    : FrozenVector(vector, parent)
{
    connect(parent, &FrozenVector::removedAudio, this, &CurrentState::removeAudio);
}

void audios::CurrentState::removeAudio(const Audio &audio)
{
    const int index = indexOf(audio);
    if (index == -1)
        return;

    remove(index);
    emit removed(index);
    emit removedAudio(audio);
}
