#ifndef BASSWRAPPER_HPP
#define BASSWRAPPER_HPP

#include <QHash>

#include "bass/bass.h"

#include "logger.hpp"

class BassWrapper
{
public:
    BassWrapper();
    ~BassWrapper();

    bool start();
    bool pause();
    bool stop();

private:
    bool init();
    bool free();

    void error();

    const static QHash<int, QString> _errors;
};

#endif // BASSWRAPPER_HPP
