#ifndef RANDUTIL_HPP
#define RANDUTIL_HPP

#include <QRandomGenerator64>

class RandUtil
{
public:
    static double random();
    static qint64 randint(qint64 min, qint64 max);
    static qint64 randint(qint64 max);
};

#endif // RANDUTIL_HPP
