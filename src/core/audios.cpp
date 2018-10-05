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

Audio *Audios::at(int index)
{
    return (*this)[index];
}

Audio *Audios::at(int index) const
{
    return Audio::vector::at(index);
}

Audio *Audios::first() const
{
    return Audio::vector::first();
}

Audio *Audios::last() const
{
    return Audio::vector::last();
}

bool Audios::isEmpty() const
{
    return Audio::vector::isEmpty();
}

int Audios::size() const
{
    return Audio::vector::size();
}

int Audios::indexOf(Audio *audio, int index) const
{
    return Audio::vector::indexOf(audio, index);
}

void Audios::clear()
{
    Audio::vector::clear();
}

void Audios::reserve(int size)
{
    Audio::vector::reserve(size);
}

void Audios::insert(int index, Audio *audio)
{
    connect(audio, &Audio::updated, this, &Audios::onAudioUpdated);
    Audio::vector::insert(index, audio);
    emit inserted(index);
}

void Audios::append(Audio *audio)
{
    connect(audio, &Audio::updated, this, &Audios::onAudioUpdated);
    Audio::vector::append(audio);
    emit inserted(size() - 1);
}

void Audios::remove(int index)
{
    Audio *audio = at(index);
    disconnect(audio, &Audio::updated, this, &Audios::onAudioUpdated);
    Audio::vector::remove(index);
    emit removed(index);
    emit removedAudio(audio);
}

void Audios::remove(Audio *audio)
{
    const int index = indexOf(audio);
    if (index != -1)
        remove(index);
}

void Audios::move(int from, int to)
{
    Audio::vector::move(from, to);
    emit moved(from, to);
}

Audios::iterator Audios::insert(Audios::iterator before, Audio *audio)
{
    connect(audio, &Audio::updated, this, &Audios::onAudioUpdated);
    auto position = Audio::vector::insert(before, audio);
    emit inserted(static_cast<int>(position - begin()));
    return position;
}

Audios::iterator Audios::erase(Audios::iterator position)
{
    disconnect(*position, &Audio::updated, this, &Audios::onAudioUpdated);
    auto next = Audio::vector::erase(position);
    emit removed(static_cast<int>(position - begin()));
    emit removedAudio(*position);
    return next;
}

Audios::iterator Audios::begin()
{
    return Audio::vector::begin();
}

Audios::iterator Audios::end()
{
    return Audio::vector::end();
}

Audios::const_iterator Audios::cbegin() const
{
    return Audio::vector::cbegin();
}

Audios::const_iterator Audios::cend() const
{
    return Audio::vector::cend();
}

Audios &Audios::operator<<(Audio *audio)
{
    append(audio);
    return *this;
}

Audio *Audios::operator[](int index)
{
    return Audio::vector::operator[](index);
}

Audios *Audios::currentState()
{
    Audios *audios = new Audios(*this, this);
    connect(this, &Audios::removedAudio, audios, &Audios::onParentAudioRemoved);
    return audios;
}

void Audios::onAudioUpdated(Audio *audio)
{
    const int index = indexOf(audio);
    if (index != -1)
        emit updated(indexOf(audio));
}

void Audios::onParentAudioRemoved(Audio *audio)
{
    remove(audio);
}
