#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QVariant>
#include <QVector>

#include "config.hpp"
#include "constants.hpp"

extern void log(const QString &message, const QVector<QVariant> &args = {});

namespace LoggerPrivate
{
    extern QString createLog(QString message, const QVector<QVariant> &args);
}

#endif // LOGGER_HPP
