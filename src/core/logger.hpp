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

extern void log(const QString &message,
                const QVariant &arg1 = QVariant(),
                const QVariant &arg2 = QVariant(),
                const QVariant &arg3 = QVariant(),
                const QVariant &arg4 = QVariant());

#endif // LOGGER_HPP
