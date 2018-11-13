#ifndef BASS_SYNCWRAPPER_HPP
#define BASS_SYNCWRAPPER_HPP

#include <functional>

#include <bass/bass.h>

#include "core/macros.hpp"
#include "core/bass/basserror.hpp"

namespace bass
{

class SyncWrapper : private BassError
{
public:
    SyncWrapper();

    EGG_CPROP(std::function<void(void *)>, function, setFunction, function)
    EGG_PPROP(void *, functionData, setFunctionData,  functionData)

    bool isValid() const;

    bool setSync(HSTREAM handle);
    bool removeSync(HSTREAM handle);

private:
    static void CALLBACK callback(HSYNC handle, DWORD channel, DWORD data, void *user);

    HSYNC m_handle;
};

}

#endif // BASS_SYNCWRAPPER_HPP
