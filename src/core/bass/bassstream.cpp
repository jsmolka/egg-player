#include "bassstream.hpp"

#include "core/utils.hpp"

bass::Stream::Stream()
    : m_handle(0)
    , m_sync(0)
{

}

HSTREAM bass::Stream::handle() const
{
    return m_handle;
}

HSYNC bass::Stream::sync() const
{
    return m_sync;
}

bool bass::Stream::isHandleValid() const
{
    return m_handle != 0;
}

bool bass::Stream::isSyncValid() const
{
    return m_sync != 0;
}

bool bass::Stream::isPlaying() const
{
    return BASS_ChannelIsActive(m_handle) == BASS_ACTIVE_PLAYING;
}

bool bass::Stream::isPaused() const
{
    return BASS_ChannelIsActive(m_handle) == BASS_ACTIVE_PAUSED;
}

bool bass::Stream::isStopped() const
{
    return BASS_ChannelIsActive(m_handle) == BASS_ACTIVE_STOPPED;
}

bool bass::Stream::isStalled() const
{
    return BASS_ChannelIsActive(m_handle) == BASS_ACTIVE_STALLED;
}

bool bass::Stream::play() const
{
    if (isPlaying())
        return true;

    return check(BASS_ChannelPlay(m_handle, false));
}

bool bass::Stream::pause() const
{
    if (isPaused() || isStopped())
        return true;

    return check(BASS_ChannelPause(m_handle));
}

bool bass::Stream::create(Audio *audio)
{
    if (!free())
        return false;

    m_handle = BASS_StreamCreateFile(false, Util::toWString(audio->file()), 0, 0, BASS_ASYNCFILE);

    return check(isHandleValid());
}

bool bass::Stream::free()
{
    if (!isHandleValid())
        return true;

    if (check(BASS_StreamFree(m_handle)))
        m_handle = 0;

    return !isHandleValid();
}

bool bass::Stream::setPosition(int position) const
{
    const QWORD bytes = BASS_ChannelSeconds2Bytes(m_handle, static_cast<double>(position));
    return check(BASS_ChannelSetPosition(m_handle, bytes, BASS_POS_BYTE));
}

int bass::Stream::position() const
{
    const QWORD bytes = BASS_ChannelGetPosition(m_handle, BASS_POS_BYTE);
    const double position = BASS_ChannelBytes2Seconds(m_handle, bytes);
    if (!check(position >= 0))
        return -1;

    return static_cast<int>(position);
}

bool bass::Stream::setVolume(float volume) const
{
    return check(BASS_ChannelSetAttribute(m_handle, BASS_ATTRIB_VOL, volume));
}

float bass::Stream::volume() const
{
    float volume = -1;
    check(BASS_ChannelGetAttribute(m_handle, BASS_ATTRIB_VOL, &volume));

    return volume;
}

bool bass::Stream::setDevice(DWORD device) const
{
    return check(BASS_ChannelSetDevice(m_handle, device));
}

DWORD bass::Stream::device() const
{
    const DWORD device = BASS_ChannelGetDevice(m_handle);
    check(device != 0);

    return device;
}

bool bass::Stream::setCallback(SYNCPROC *proc, void *user)
{
    m_sync = BASS_ChannelSetSync(m_handle, BASS_SYNC_END, 0, proc, user);

    return check(isSyncValid());
}

bool bass::Stream::removeCallback()
{
    if (!isSyncValid())
        return true;

    if (check(BASS_ChannelRemoveSync(m_handle, m_sync)))
        m_sync = 0;

    return !isSyncValid();
}
