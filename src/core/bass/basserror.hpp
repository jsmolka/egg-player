#ifndef BASSERROR_HPP
#define BASSERROR_HPP

#include <bass/bass.h>

#include "core/globals.hpp"

class BassError
{
protected:
    static bool check(bool value);

private:
    static void error();
};

#endif // BASSERROR_HPP
