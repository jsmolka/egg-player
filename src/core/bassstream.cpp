#include "bassstream.hpp"

BassStream::BassStream()
    : m_handle(0)
    , m_sync(0)
{

}

BassStream::~BassStream()
{

}

HSTREAM BassStream::handle() const
{
    return m_handle;
}

HSYNC BassStream::sync() const
{
    return m_sync;
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

    const bool success = BASS_ChannelPlay(m_handle, false);
    if (!success)
        error();

    return success;
}

bool BassStream::pause()
{
    if (isPaused() || isStopped())
        return true;

    const bool success = BASS_ChannelPause(m_handle);
    if (!success)
        error();

    return success;
}

bool BassStream::create(Audio *audio)
{
    if (!free())
        return false;

    m_handle = BASS_StreamCreateFile(false, audio->widePath(), 0, 0, BASS_ASYNCFILE);

    return isValid();
}

bool BassStream::free()
{
    if (!isValid())
        return true;

    const bool success = BASS_StreamFree(m_handle);
    if (success)
        m_handle = 0;
    else
        error();

    return success;
}

bool BassStream::setPosition(int position)
{
    const QWORD bytes = BASS_ChannelSeconds2Bytes(m_handle, static_cast<double>(position));
    const bool success = bytes != -1 && BASS_ChannelSetPosition(m_handle, bytes, BASS_POS_BYTE);
    if (!success)
        error();

    return success;
}

int BassStream::position() const
{
    const QWORD bytes = BASS_ChannelGetPosition(m_handle, BASS_POS_BYTE);
    if (bytes == -1)
    {
        error();
        return -1;
    }

    const int position = static_cast<int>(BASS_ChannelBytes2Seconds(m_handle, bytes));
    if (position < 0)
    {
        error();
        return -1;
    }

    return position;
}

bool BassStream::setVolume(float volume)
{
    const bool success = BASS_ChannelSetAttribute(m_handle, BASS_ATTRIB_VOL, volume);
    if (!success)
        error();

    return success;
}

float BassStream::volume() const
{
    float volume = -1;
    if (!BASS_ChannelGetAttribute(m_handle, BASS_ATTRIB_VOL, &volume))
        error();

    return volume;
}

bool BassStream::setDevice(DWORD device)
{
    const bool success = BASS_ChannelSetDevice(m_handle, device);
    if (!success)
        error();

    return success;
}

DWORD BassStream::device() const
{
    if (BASS_ChannelGetDevice(m_handle) == -1)
        error();

    return BASS_ChannelGetDevice(m_handle);
}

bool BassStream::setCallback(SYNCPROC *proc, void *user)
{
    m_sync = BASS_ChannelSetSync(m_handle, BASS_SYNC_END, 0, proc, user);
    const bool success = m_sync != 0;
    if (!success)
        error();

    return success;
}

bool BassStream::removeCallback()
{
    if (m_sync == 0)
        return true;

    const bool success = BASS_ChannelRemoveSync(m_handle, m_sync);
    if (success)
        m_sync = 0;
    else
        error();

    return success;
}
