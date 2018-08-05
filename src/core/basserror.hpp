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

private:
    static QHash<int, QString> s_errors;
};

#endif // BASSERROR_HPP
