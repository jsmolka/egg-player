#include "bass.hpp"

#include "core/macros.hpp"
#include "core/bass/bassinitializer.hpp"

Bass::Bass()
{
    bass::BassInitializer::init();
}

Bass::~Bass()
{
    bass::BassInitializer::free();
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
