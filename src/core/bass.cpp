#include "bass.hpp"

Bass::Bass()
{
    _instances++;
    if (_instances == 1)
    {
        init();

        if (HIWORD(BASS_GetVersion()) != BASSVERSION)
            log("Bass: Different BASS versions %1 and %2", {static_cast<int>(BASS_GetVersion()), BASSVERSION});
    }
}

Bass::~Bass()
{
    _instances--;
    if (_instances == 0)
        free();
}

BassStream * Bass::stream()
{
    return &m_stream;
}

bool Bass::start()
{
    return call(&BASS_Start);
}

bool Bass::pause()
{
    return call(&BASS_Pause);
}

bool Bass::stop()
{
    return call(&BASS_Stop);
}

bool Bass::setVolume(float volume)
{
    return BASS_SetVolume(volume);
}

float Bass::volume()
{
    if (BASS_GetVolume() == -1)
        error();

    return BASS_GetVolume();
}

bool Bass::setDevice(DWORD device)
{
    return BASS_SetDevice(device);
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

bool Bass::init()
{
    if (!BASS_Init(-1, 44100, 0, 0, NULL))
    {
        error();
        return false;
    }
    return true;
}

bool Bass::free()
{
    return call(&BASS_Free);
}

bool Bass::call(BOOL(*func)())
{
    if (!func())
    {
        error();
        return false;
    }
    return true;
}

int Bass::_instances = 0;
