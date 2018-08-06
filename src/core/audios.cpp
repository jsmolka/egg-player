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

AudioVector::iterator Audios::begin()
{
    return m_vector.begin();
}

AudioVector::iterator Audios::end()
{
    return m_vector.end();
}

AudioVector::const_iterator Audios::begin() const
{
    return m_vector.begin();
}

AudioVector::const_iterator Audios::end() const
{
    return m_vector.end();
}

int Audios::size() const
{
    return m_vector.size();
}

bool Audios::isEmpty() const
{
    return m_vector.isEmpty();
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
    emit inserted(m_vector.size() - 1);
}

void Audios::remove(int index)
{
    disconnect(at(index), &Audio::updated, this, &Audios::updated);
    m_vector.remove(index);
    emit removed(index);
}

Audios & Audios::operator<<(Audio *audio)
{
    append(audio);
    return *this;
}
