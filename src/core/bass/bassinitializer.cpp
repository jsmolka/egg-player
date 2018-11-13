#include "bassinitializer.hpp"

#include <bass/bass.h>

#include "core/logger.hpp"

bool bass::BassInitializer::init()
{
    if (!isValidVersion() || !setConfig())
        return false;

    return check(BASS_Init(-1, 44100, 0, nullptr, nullptr));
}

bool bass::BassInitializer::free()
{
    return check(BASS_Free());
}

bool bass::BassInitializer::isValidVersion()
{
    if (HIWORD(BASS_GetVersion()) != BASSVERSION)
    {
        EGG_LOG("Different BASS versions");
        return false;
    }
    return true;
}

bool bass::BassInitializer::setConfig()
{
    return check(BASS_SetConfig(BASS_CONFIG_DEV_DEFAULT, 1));
}
