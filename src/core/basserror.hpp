#ifndef BASSERROR_HPP
#define BASSERROR_HPP

#include <QHash>

#include "bass/bass.h"

#include "logger.hpp"

class BassError
{
public:
    BassError();
    ~BassError();

protected:
    static void error();
};

#endif // BASSERROR_HPP
