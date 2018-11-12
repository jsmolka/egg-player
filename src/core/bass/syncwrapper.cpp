#include "syncwrapper.hpp"

#include <QtGlobal>

bass::SyncWrapper::SyncWrapper()
    : m_handle(0)
{

}

bool bass::SyncWrapper::isValid() const
{
    return m_handle != 0;
}

bool bass::SyncWrapper::setSync(HSTREAM handle)
{
    m_handle = BASS_ChannelSetSync(handle, BASS_SYNC_END, 0, callback, this);

    return check(isValid());
}

bool bass::SyncWrapper::removeSync(HSTREAM handle)
{
    if (!isValid())
        return true;

    if (check(BASS_ChannelRemoveSync(handle, m_handle)))
    {
        m_handle = 0;
        return true;
    }
    return false;
}

void bass::SyncWrapper::callback(HSYNC handle, DWORD channel, DWORD data, void *user)
{
    Q_UNUSED(handle);
    Q_UNUSED(channel);
    Q_UNUSED(data);

    SyncWrapper *sync = static_cast<SyncWrapper *>(user);
    sync->function()(sync->functionData());
}
