#include "audiosbase.hpp"

audios::Base::Base(QObject *parent)
    : Base(Audio::vector(), parent)
{

}

audios::Base::Base(const Audio::vector &vector, QObject *parent)
    : QObject(parent)
    , Audio::vector(vector)
{

}

audios::Base::~Base()
{

}

Audio::vector audios::Base::vector() const
{
    return static_cast<Audio::vector>(*this);
}
