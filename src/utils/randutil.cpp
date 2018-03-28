#include "randutil.hpp"

double RandUtil::random()
{
    return QRandomGenerator::global()->generateDouble();
}

unsigned int RandUtil::randmax()
{
    return QRandomGenerator::global()->generate();
}

int RandUtil::randint(int min, int max)
{
    return min + randmax() % max;
}

int RandUtil::randint(int max)
{
    return randint(0, max);
}
