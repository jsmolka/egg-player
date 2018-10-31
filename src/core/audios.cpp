#include "audios.hpp"

Audios::Audios(QObject *parent)
    : Audios(Audio::vector(), parent)
{

}

Audios::Audios(const Audio::vector &vector, QObject *parent)
    : QObject(parent)
    , Audio::vector(vector)
{

}

Audio::vector Audios::vector() const
{
    return static_cast<Audio::vector>(*this);
}

void Audios::insert(int index, Audio *audio)
{
    audio->setParent(this);
    Audio::vector::insert(index, audio);
    emit inserted(index);
}

void Audios::append(Audio *audio)
{
    audio->setParent(this);
    Audio::vector::append(audio);
    emit inserted(size() - 1);
}

void Audios::remove(int index)
{
    Audio *audio = at(index);
    Audio::vector::remove(index);
    emit removed(index);
    emit removedAudio(audio);
}

Audios::iterator Audios::insert(Audios::iterator before, Audio *audio)
{
    audio->setParent(this);
    auto position = Audio::vector::insert(before, audio);
    emit inserted(static_cast<int>(position - begin()));

    return position;
}

Audios::iterator Audios::erase(Audios::iterator position)
{
    auto next = Audio::vector::erase(position);
    emit removed(static_cast<int>(position - begin()));
    emit removedAudio(*position);

    return next;
}

int Audios::lowerBound(Audio *audio)
{
    int low = 0;
    int high = size();
    while (low < high)
    {
        const int mid = (low + high) / 2;
        const int diff = audio->tag().title().compare(at(mid)->tag().title(), Qt::CaseInsensitive);
        if (diff < 0)
            high = mid;
        else
            low = mid + 1;
    }
    return low;
}

Audios *Audios::currentState()
{
    Audios *state = new Audios(*this, this);
    connect(this, &Audios::removedAudio, state, &Audios::removeAudio);

    return state;
}

Audios &Audios::operator<<(Audio *audio)
{
    append(audio);

    return *this;
}

void Audios::removeAudio(Audio *audio)
{
    const int index = indexOf(audio);
    if (index != -1)
        remove(index);
}
