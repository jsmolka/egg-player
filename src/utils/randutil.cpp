#include "randutil.hpp"

qreal RandUtil::random()
{
    return QRandomGenerator64::global()->generateDouble();
}

quint64 RandUtil::randmax()
{
    return QRandomGenerator64::global()->generate64();
}

qint64 RandUtil::randint(qint64 min, qint64 max)
{
    return min + randmax() % max;
}

qint64 RandUtil::randint(qint64 max)
{
    return randint(0, max);
}
