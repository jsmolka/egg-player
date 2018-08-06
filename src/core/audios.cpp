#include "audios.hpp"

Audios::Audios(QObject *parent)
    : Audios(AudioVector(), parent)
{

}

Audios::Audios(const AudioVector &vector, QObject *parent)
    : QObject(parent)
    , m_vector(vector)
{

}

Audios::~Audios()
{

}

AudioVector Audios::vector() const
{
    return m_vector;
}

Audio * Audios::at(int index)
{
    return m_vector[index];
}

Audio * Audios::takeAt(int index)
{
    return m_vector.takeAt(index);
}

Audio * Audios::takeFirst()
{
    return m_vector.takeFirst();
}

Audio * Audios::takeLast()
{
    return m_vector.takeLast();
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
    m_vector.insert(index, audio);
    connect(audio, &Audio::updated, this, &Audios::updated);
    emit inserted(index);
}

void Audios::append(Audio *audio)
{
    m_vector.append(audio);
    connect(audio, &Audio::updated, this, &Audios::updated);
    emit inserted(size() - 1);
}

void Audios::remove(int index)
{
    disconnect(at(index), &Audio::updated, this, &Audios::updated);
    m_vector.remove(index);
    emit removed(index);
}

AudioVector::iterator Audios::insert(AudioVector::iterator before, Audio *audio)
{
    auto position = m_vector.insert(before, audio);
    connect(audio, &Audio::updated, this, &Audios::updated);
    emit inserted(position - begin());
    return position;
}

AudioVector::iterator Audios::erase(AudioVector::iterator position)
{
    disconnect(*position, &Audio::updated, this, &Audios::updated);
    auto next = m_vector.erase(position);
    emit removed(position - begin());
    return next;
}

AudioVector::iterator Audios::begin()
{
    return m_vector.begin();
}

AudioVector::iterator Audios::end()
{
    return m_vector.end();
}

AudioVector::reverse_iterator Audios::rbegin()
{
    return m_vector.rbegin();
}

AudioVector::reverse_iterator Audios::rend()
{
    return m_vector.rend();
}

AudioVector::const_iterator Audios::cbegin() const
{
    return m_vector.cbegin();
}

AudioVector::const_iterator Audios::cend() const
{
    return m_vector.cend();
}

AudioVector::const_reverse_iterator Audios::crbegin() const
{
    return m_vector.crbegin();
}

AudioVector::const_reverse_iterator Audios::crend() const
{
    return m_vector.crend();
}

Audios & Audios::operator<<(Audio *audio)
{
    append(audio);
    return *this;
}
