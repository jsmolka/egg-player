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
    void error();

private:
    const static QHash<int, QString> errors;
};

#endif // BASSERROR_HPP
