#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "config.hpp"
#include "constants.hpp"
#include "types.hpp"

extern void log(const QString &message, const StringList &args = {});

namespace LoggerPrivate
{
    extern QString createLog(QString message, const StringList &args);
}

#endif // LOGGER_HPP
