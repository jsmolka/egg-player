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

bool BassStream::isPlaying() const
{
    return BASS_ChannelIsActive(m_handle) == BASS_ACTIVE_PLAYING;
}

bool BassStream::isPaused() const
{
    return BASS_ChannelIsActive(m_handle) == BASS_ACTIVE_PAUSED;
}

bool BassStream::isStopped() const
{
    return BASS_ChannelIsActive(m_handle) == BASS_ACTIVE_STOPPED;
}

bool BassStream::isStalled() const
{
    return BASS_ChannelIsActive(m_handle) == BASS_ACTIVE_STALLED;
}

bool BassStream::play()
{
    if (isPlaying())
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
    if (isPaused() || isStopped())
        return true;

    if (!BASS_ChannelPause(m_handle))
    {
        error();
        return false;
    }
    return true;
}

bool BassStream::create(Audio *audio, bool prescan)
{
    if (!free())
        return false;

    DWORD flags = prescan ? BASS_STREAM_PRESCAN : 0 | BASS_ASYNCFILE;
    m_handle = BASS_StreamCreateFile(false, audio->pathWChar(), 0, 0, flags);
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

bool BassStream::setPosition(int position)
{
    QWORD bytes = BASS_ChannelSeconds2Bytes(m_handle, static_cast<double>(position));
    if (bytes == -1 || !BASS_ChannelSetPosition(m_handle, bytes, BASS_POS_BYTE))
    {
        error();
        return false;
    }
    return true;
}

int BassStream::position()
{
    QWORD bytes = BASS_ChannelGetPosition(m_handle, BASS_POS_BYTE);
    int position = static_cast<int>(BASS_ChannelBytes2Seconds(m_handle, bytes));
    if (position < 0)
    {
        error();
        return -1;
    }
    return position;
}

bool BassStream::setVolume(float volume)
{
    if (!BASS_ChannelSetAttribute(m_handle, BASS_ATTRIB_VOL, volume))
    {
        error();
        return false;
    }
    return true;
}

float BassStream::volume()
{
    float volume;
    if (!BASS_ChannelGetAttribute(m_handle, BASS_ATTRIB_VOL, &volume))
    {
        error();
        return -1;
    }
    return volume;
}

bool BassStream::setDevice(DWORD device)
{
    if (!BASS_ChannelSetDevice(m_handle, device))
    {
        error();
        return false;
    }
    return true;
}

DWORD BassStream::device()
{
    return BASS_ChannelGetDevice(m_handle);
}
