#include "bass.hpp"

#include "core/logger.hpp"
#include "core/macros.hpp"

Bass::Bass()
{
    if (isValidVersion() && setConfig())
        init();
}

Bass::~Bass()
{
    free();
}

const bass::StreamWrapper &Bass::stream() const
{
    return m_stream;
}

const bass::SyncWrapper &Bass::sync() const
{
    return m_sync;
}

bass::StreamWrapper &Bass::stream()
{
    return EGG_REF_CAST(Bass, bass::StreamWrapper, stream);
}

bass::SyncWrapper &Bass::sync()
{
    return EGG_REF_CAST(Bass, bass::SyncWrapper, sync);
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
