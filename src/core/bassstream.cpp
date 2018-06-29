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

bool BassStream::play()
{
    if (!isValid())
        return false;

    if (BASS_ChannelIsActive(m_handle) == BASS_ACTIVE_PLAYING)
        return true;

    if (!BASS_ChannelPlay(m_handle, false))
    {
        error();
        return false;
    }
    return true;
}

bool BassStream::pause()
{
    if (!isValid())
        return false;

    if (BASS_ChannelIsActive(m_handle) == BASS_ACTIVE_PAUSED
            || BASS_ChannelIsActive(m_handle) == BASS_ACTIVE_STOPPED)
        return true;

    if (!BASS_ChannelPause(m_handle))
    {
        error();
        return false;
    }
    return true;
}

bool BassStream::create(Audio *audio, bool scan)
{
    if (!free())
        return false;

    m_handle = BASS_StreamCreateFile(false, audio->pathWChar(), 0, 0, scan ? BASS_STREAM_PRESCAN : 0);
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

bool BassStream::setPosition(qint64 position)
{
    if (!isValid())
        return false;

    double seconds = static_cast<double>(position) / 1000.0;
    QWORD bytes = BASS_ChannelSeconds2Bytes(m_handle, seconds);
    if (!BASS_ChannelSetPosition(m_handle, bytes, 0))
    {
        error();
        return false;
    }
    return true;
}

qint64 BassStream::position()
{
    if (!isValid())
        return -1;

    QWORD bytes = BASS_ChannelGetPosition(m_handle, 0);
    return BASS_ChannelBytes2Seconds(m_handle, bytes) * 1000;
}

bool BassStream::setVolume(int volume)
{
    if (!isValid())
        return false;

    if (!BASS_ChannelSetAttribute(m_handle, BASS_ATTRIB_VOL, static_cast<float>(volume) / 1000.0))
    {
        error();
        return false;
    }
    return true;
}

int BassStream::volume()
{
    return 0;
}
