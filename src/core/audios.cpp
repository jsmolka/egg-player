#include "audios.hpp"

Audios::Audios(QObject *parent)
    : Audios(Audio::vector(), parent)
{

}

Audios::Audios(const Audio::vector &vector, QObject *parent)
    : QObject(parent)
    , m_vector(vector)
{

}

Audios::~Audios()
{

}

void Audios::setVector(const Audio::vector &vector)
{
    m_vector = vector;
}

Audio::vector Audios::vector() const
{
    return m_vector;
}

Audio *Audios::at(int index)
{
    return m_vector[index];
}

Audio *Audios::first()
{
    return m_vector.first();
}

Audio *Audios::last()
{
    return m_vector.last();
}

bool Audios::isEmpty() const
{
    return m_vector.isEmpty();
}

int Audios::size() const
{
    return m_vector.size();
}

int Audios::indexOf(Audio *audio) const
{
    return m_vector.indexOf(audio);
}

void Audios::clear()
{
    m_vector.clear();
}

void Audios::reserve(int size)
{
    m_vector.reserve(size);
}

void Audios::move(int from, int to)
{
    m_vector.move(from, to);
}

void Audios::insert(int index, Audio *audio)
{
    connect(audio, &Audio::updated, this, &Audios::onAudioUpdated);
    m_vector.insert(index, audio);
    emit inserted(index);
}

void Audios::append(Audio *audio)
{
    connect(audio, &Audio::updated, this, &Audios::onAudioUpdated);
    m_vector.append(audio);
    emit inserted(size() - 1);
}

void Audios::remove(int index)
{
    disconnect(at(index), &Audio::updated, this, &Audios::onAudioUpdated);
    m_vector.remove(index);
    emit removed(index);
}

void Audios::remove(Audio *audio)
{
    const int index = indexOf(audio);
    if (index != -1)
        remove(index);
}

Audio::vector::iterator Audios::insert(Audio::vector::iterator before, Audio *audio)
{
    connect(audio, &Audio::updated, this, &Audios::onAudioUpdated);
    auto position = m_vector.insert(before, audio);
    emit inserted(position - m_vector.begin());
    return position;
}

Audio::vector::iterator Audios::erase(Audio::vector::iterator position)
{
    disconnect(*position, &Audio::updated, this, &Audios::onAudioUpdated);
    auto next = m_vector.erase(position);
    emit removed(position - begin());
    return next;
}

Audio::vector::iterator Audios::begin()
{
    return m_vector.begin();
}

Audio::vector::iterator Audios::end()
{
    return m_vector.end();
}

Audio::vector::const_iterator Audios::cbegin() const
{
    return m_vector.cbegin();
}

Audio::vector::const_iterator Audios::cend() const
{
    return m_vector.cend();
}

Audios &Audios::operator<<(Audio *audio)
{
    append(audio);
    return *this;
}

void Audios::onAudioUpdated(Audio *audio)
{
    for (int i = 0; i < size(); ++i)
    {
        if (at(i) == audio)
        {
            emit updated(i);
            return;
        }
    }
}
