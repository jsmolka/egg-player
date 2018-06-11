#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "config.hpp"
#include "constants.hpp"
#include "types.hpp"

namespace Logger
{
    /*!
     * Logs a message.
     */
    extern void log(const QString &message, const StringList &args = {});
    /*!
     * Creates a log message.
     */
    extern QString createLog(QString message, const StringList &args);
}

#endif // LOGGER_HPP
