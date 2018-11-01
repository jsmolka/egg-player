#include "bass.hpp"

#include "core/globals.hpp"

Bass::Bass()
{
    if (isValidVersion() && setConfig())
        init();
}

Bass::~Bass()
{
    free();
}

Bass &Bass::instance()
{
    static Bass bass;

    return bass;
}

bass::Stream &Bass::stream()
{
    return m_stream;
}

bool Bass::start()
{
    return check(BASS_Start());
}

bool Bass::pause()
{
    return check(BASS_Pause());
}

bool Bass::stop()
{
    return check(BASS_Stop());
}

bool Bass::setVolume(float volume)
{
    return check(BASS_SetVolume(volume));
}

float Bass::volume()
{
    const float volume = BASS_GetVersion();
    check(!qFuzzyCompare(volume, -1));

    return volume;
}

bool Bass::setDevice(DWORD device)
{
    return check(BASS_SetDevice(device));
}

DWORD Bass::device()
{
    const DWORD device = BASS_GetDevice();
    check(device != 0);

    return device;
}

BASS_DEVICEINFO Bass::deviceInfo()
{
    BASS_DEVICEINFO info;
    check(BASS_GetDeviceInfo(device(), &info));

    return info;
}

bool Bass::isValidVersion()
{
    if (HIWORD(BASS_GetVersion()) != BASSVERSION)
    {
        EGG_LOG("Different BASS versions");
        return false;
    }
    return true;
}

bool Bass::setConfig()
{
    return check(BASS_SetConfig(BASS_CONFIG_DEV_DEFAULT, 1));
}

bool Bass::init()
{
    return check(BASS_Init(-1, 44100, 0, nullptr, nullptr));
}

bool Bass::free()
{
    return check(BASS_Free());
}
