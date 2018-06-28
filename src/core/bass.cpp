#include "bass.hpp"

Bass::Bass()
{
    init();

    if (BASS_GetVersion() != BASSVERSION)
        log("Bass: Invalid versions %1 and %2", {static_cast<int>(BASS_GetVersion()), BASSVERSION});
}

Bass::~Bass()
{
    free();
}

BassStream Bass::stream()
{
    return m_stream;
}

bool Bass::start()
{
    if (!BASS_Start())
    {
        error();
        return false;
    }
    return true;
}

bool Bass::pause()
{
    if (!BASS_Pause())
    {
        error();
        return false;
    }
    return true;
}

bool Bass::stop()
{
    if (!BASS_Stop())
    {
        error();
        return false;
    }
    return true;
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
        if (BASS_ErrorGetCode() != BASS_ERROR_ALREADY)
        {
            error();
            return false;
        }
    }
    return true;
}

bool Bass::free()
{
    if (!BASS_Free())
    {
        error();
        return false;
    }
    return true;
}
