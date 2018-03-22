#include "randutil.hpp"

qreal RandUtil::random()
{
    return QRandomGenerator64::global()->generateDouble();
}

qint64 RandUtil::randint(qint64 min, qint64 max)
{
    return min + QRandomGenerator64::global()->generate64() % max;
}

qint64 RandUtil::randint(qint64 max)
{
    return randint(0, max);
}
