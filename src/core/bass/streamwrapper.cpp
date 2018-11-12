#include "streamwrapper.hpp"

#include "core/config.hpp"
#include "core/utils.hpp"

bass::StreamWrapper::StreamWrapper()
    : m_handle(0)
{

}

HSTREAM bass::StreamWrapper::handle() const
{
    return m_handle;
}

bool bass::StreamWrapper::isValid() const
{
    return m_handle != 0;
}

bool bass::StreamWrapper::isPlaying() const
{
    if (!isValid())
        return false;

    return BASS_ChannelIsActive(m_handle) == BASS_ACTIVE_PLAYING;
}

bool bass::StreamWrapper::setPosition(int position) const
{
    if (!isValid())
        return false;

    const QWORD bytes = BASS_ChannelSeconds2Bytes(m_handle, static_cast<int>(position));

    return check(BASS_ChannelSetPosition(m_handle, bytes, BASS_POS_BYTE));
}

int bass::StreamWrapper::position() const
{
    if (!isValid())
        return -1;

    const QWORD bytes = BASS_ChannelGetPosition(m_handle, BASS_POS_BYTE);
    const double position = BASS_ChannelBytes2Seconds(m_handle, bytes);

    return check(position >= 0) ? qRound(position) : -1;
}

bool bass::StreamWrapper::setVolume(float volume) const
{
    if (!isValid())
        return false;

    return check(BASS_ChannelSetAttribute(m_handle, BASS_ATTRIB_VOL, volume));
}

float bass::StreamWrapper::volume() const
{
    if (!isValid())
        return -1;

    float volume = -1;
    check(BASS_ChannelGetAttribute(m_handle, BASS_ATTRIB_VOL, &volume));

    return volume;
}

bool bass::StreamWrapper::play() const
{
    if (!isValid())
        return false;

    if (isPlaying())
        return true;

    return check(BASS_ChannelPlay(m_handle, false));
}

bool bass::StreamWrapper::pause() const
{
    if (!isValid())
        return false;

    if (!isPlaying())
        return true;

    return check(BASS_ChannelPause(m_handle));
}

bool bass::StreamWrapper::create(Audio *audio)
{
    if (isValid())
    {
        if (!free())
            return false;
    }

    m_handle = BASS_StreamCreateFile(false, Util::toWString(audio->file()), 0, 0, BASS_ASYNCFILE);

    return check(isValid());
}

bool bass::StreamWrapper::free()
{
    if (check(BASS_StreamFree(m_handle)))
    {
        m_handle = 0;
        return true;
    }
    return false;
}
