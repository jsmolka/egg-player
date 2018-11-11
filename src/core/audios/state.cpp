#include "state.hpp"

audios::State::State(const Audio::vector &vector, StaticVector *parent)
    : StaticVector(vector, parent)
{
    connect(parent, &StaticVector::removedAudio, this, &State::removeAudio);
}

void audios::State::removeAudio(Audio *audio)
{
    const int index = indexOf(audio);
    if (index == -1)
        return;

    remove(index);
    emit removed(index);
    emit removedAudio(audio);
}
