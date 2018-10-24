#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <QString>
#include <QVector>
#include <QVariant>

namespace Logger
{
    extern void log(const QString &message, const QString &func, const QVector<QVariant> &args);
}

#define EGG_LOG(message, ...) Logger::log(message, __FUNCTION__, {__VA_ARGS__})
#define LOG EGG_LOG

#endif // LOGGER_HPP
