#include "frozenvector.hpp"

audios::FrozenVector::FrozenVector(QObject *parent)
    : FrozenVector(Audio::vector(), parent)
{

}

audios::FrozenVector::FrozenVector(const Audio::vector &vector, QObject *parent)
    : QObject(parent)
    , Audio::vector(vector)
{

}

audios::FrozenVector::~FrozenVector()
{

}

Audio::vector audios::FrozenVector::vector() const
{
    return static_cast<Audio::vector>(*this);
}
