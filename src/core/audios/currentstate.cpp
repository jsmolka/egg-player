#include "currentstate.hpp"

audios::CurrentState::CurrentState(const QVector<Audio> &vector, AudiosBase *parent)
    : AudiosBase(vector, parent)
{
    connect(parent, &AudiosBase::removedAudio, this, &CurrentState::removeAudio);
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
