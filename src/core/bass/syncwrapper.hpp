#ifndef BASS_SYNCWRAPPER_HPP
#define BASS_SYNCWRAPPER_HPP

#include <functional>

#include <bass/bass.h>

#include "core/macros.hpp"
#include "core/bass/basserror.hpp"

namespace bass
{

class SyncWrapper : protected BassError
{
public:
    SyncWrapper();

    EGG_C_PROP(std::function<void(void *)>, function, setFunction, function)
    EGG_P_PROP(void *, functionData, setFunctionData,  functionData)

    bool isValid() const;

    bool setSync(HSTREAM handle);
    bool removeSync(HSTREAM handle);

private:
    static void CALLBACK callback(HSYNC handle, DWORD channel, DWORD data, void *user);

    HSYNC m_handle;
};

}

#endif // BASS_SYNCWRAPPER_HPP
