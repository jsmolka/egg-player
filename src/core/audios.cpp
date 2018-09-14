#include "audios.hpp"

Audios::Audios(QObject *parent)
    : Audios(Audio::vector(), parent)
{

}

Audios::Audios(const Audio::vector &vector, QObject *parent)
    : QObject(parent)
    , GenericVector(vector)
{

}

void Audios::insert(int index, Audio *audio)
{
    connect(audio, &Audio::updated, this, &Audios::onAudioUpdated);
    GenericVector::insert(index, audio);
    emit inserted(index);
}

void Audios::append(Audio *audio)
{
    connect(audio, &Audio::updated, this, &Audios::onAudioUpdated);
    GenericVector::append(audio);
    emit inserted(size() - 1);
}

void Audios::remove(int index)
{
    disconnect(at(index), &Audio::updated, this, &Audios::onAudioUpdated);
    GenericVector::remove(index);
    emit removed(index);
}

void Audios::remove(Audio *audio)
{
    const int index = indexOf(audio);
    if (index != -1)
        remove(index);
}

Audios::iterator Audios::insert(iterator before, Audio *audio)
{
    connect(audio, &Audio::updated, this, &Audios::onAudioUpdated);
    auto position = GenericVector::insert(before, audio);
    emit inserted(static_cast<int>(position - begin()));
    return position;
}

Audios::iterator Audios::erase(iterator position)
{
    disconnect(*position, &Audio::updated, this, &Audios::onAudioUpdated);
    auto next = GenericVector::erase(position);
    emit removed(static_cast<int>(position - begin()));
    return next;
}

Audios &Audios::operator<<(Audio *audio)
{
    append(audio);
    return *this;
}

void Audios::onAudioUpdated(Audio *audio)
{
    emit updated(indexOf(audio));
}
