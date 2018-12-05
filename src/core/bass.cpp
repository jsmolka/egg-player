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

const bass::SyncWrapper &Bass::sync() const
{
    return m_sync;
}

bass::SyncWrapper &Bass::sync()
{
    return EGG_REF_CAST(Bass, bass::SyncWrapper, sync);
}

bool Bass::applySync()
{
    return m_sync.setSync(handle());
}

bool Bass::init()
{
    return check(BASS_Init(-1, 44100, 0, NULL, NULL));
}

bool Bass::free()
{
    return check(BASS_Free());
}

bool Bass::isValidVersion()
{
    if (HIWORD(BASS_GetVersion()) != BASSVERSION)
    {
        egg_log() << "Different BASS versions";
        return false;
    }
    return true;
}

bool Bass::setConfig()
{
    return check(BASS_SetConfig(BASS_CONFIG_DEV_DEFAULT, 1));
}
