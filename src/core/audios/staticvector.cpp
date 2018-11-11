#include "staticvector.hpp"

audios::StaticVector::StaticVector(QObject *parent)
    : StaticVector(Audio::vector(), parent)
{

}

audios::StaticVector::StaticVector(const Audio::vector &vector, QObject *parent)
    : QObject(parent)
    , Audio::vector(vector)
{

}

audios::StaticVector::~StaticVector()
{

}

Audio::vector audios::StaticVector::vector() const
{
    return static_cast<Audio::vector>(*this);
}
