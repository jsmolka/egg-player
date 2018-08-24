#include "bass.hpp"

#include "logger.hpp"

Bass::Bass()
    : m_stream()
{
    if (s_refs++ > 0)
        return;

    if (isValidVersion() && setConfig())
        init();
}

Bass::~Bass()
{
    if (--s_refs == 0)
        free();
}

BassStream &Bass::stream()
{
    return m_stream;
}

bool Bass::start()
{
    return call(BASS_Start);
}

bool Bass::pause()
{
    return call(BASS_Pause);
}

bool Bass::stop()
{
    return call(BASS_Stop);
}

bool Bass::setVolume(float volume)
{
    const bool success = BASS_SetVolume(volume);
    if (!success)
        error();

    return success;
}

float Bass::volume()
{
    if (BASS_GetVolume() == -1)
        error();

    return BASS_GetVolume();
}

bool Bass::setDevice(DWORD device)
{
    const bool success = BASS_SetDevice(device);
    if (!success)
        error();

    return success;
}

DWORD Bass::device()
{
    if (BASS_GetDevice() == -1)
        error();

    return BASS_GetDevice();
}

BASS_DEVICEINFO Bass::deviceInfo()
{
    BASS_DEVICEINFO info;
    if (!BASS_GetDeviceInfo(device(), &info))
        error();

    return info;
}

bool Bass::setConfig()
{
    const bool success = BASS_SetConfig(BASS_CONFIG_DEV_DEFAULT, 1);
    if (!success)
        error();

    return success;
}

bool Bass::isValidVersion()
{
    const bool valid = HIWORD(BASS_GetVersion()) == BASSVERSION;
    if (!valid)
        LOG("Different BASS versions");

    return valid;
}

bool Bass::init()
{
    const bool success = BASS_Init(-1, 44100, 0, 0, NULL);
    if (!success)
        error();

    return success;
}

bool Bass::free()
{
    return call(BASS_Free);
}

bool Bass::call(std::function<BOOL()> func)
{
    const bool success = func();
    if (!success)
        error();

    return success;
}

QAtomicInt Bass::s_refs = 0;
