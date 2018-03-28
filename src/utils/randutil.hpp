#ifndef RANDUTIL_HPP
#define RANDUTIL_HPP

#include <QRandomGenerator>

class RandUtil
{
public:
    static double random();
    static unsigned int randmax();
    static int randint(int min, int max);
    static int randint(int max);
};

#endif // RANDUTIL_HPP
