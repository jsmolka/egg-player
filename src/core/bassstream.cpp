#include "bassstream.hpp"

BassStream::BassStream()
    : m_handle(0)
{

}

BassStream::~BassStream()
{

}

HSTREAM BassStream::handle() const
{
    return m_handle;
}

bool BassStream::isValid() const
{
    return m_handle != 0;
}

bool BassStream::create(Audio *audio)
{
    if (!free())
        return false;

    m_handle = BASS_StreamCreateFile(false, audio->pathWChar(), 0, 0, 0);
    return isValid();
}

bool BassStream::free()
{
    if (!isValid())
        return true;

    if (!BASS_StreamFree(m_handle))
    {
        error();
        return false;
    }

    m_handle = 0;
    return true;
}
