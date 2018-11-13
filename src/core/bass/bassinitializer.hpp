#ifndef BASS_BASSINITIALIZER_HPP
#define BASS_BASSINITIALIZER_HPP

#include "core/bass/basserror.hpp"

namespace bass
{

class BassInitializer : private BassError
{
public:
    static bool init();
    static bool free();

private:
    static bool isValidVersion();
    static bool setConfig();
};

}

#endif // BASSINITIALIZER_HPP
