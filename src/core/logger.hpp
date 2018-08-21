#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <QString>
#include <QVector>
#include <QVariant>

#define LOG(message, ...) Logger::log(message, __FUNCTION__, {__VA_ARGS__})

namespace Logger
{
    extern void log(const QString &message, const QString &func, const QVector<QVariant> &args);
}

#endif // LOGGER_HPP
