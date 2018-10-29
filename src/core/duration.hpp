#ifndef DURATION_HPP
#define DURATION_HPP

#include <QString>

#include "core/globals.hpp"

class Duration
{
public:
    explicit Duration();
    explicit Duration(int secs);

    EGG_PPROP(int, secs, setSecs, secs)

    QString toString() const;
};

#endif // DURATION_HPP
