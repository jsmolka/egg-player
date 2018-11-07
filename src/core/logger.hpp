#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <QString>
#include <QVariant>
#include <QVector>

#define EGG_LOG(message, ...) Logger::log(message, __FUNCTION__, {__VA_ARGS__})

class Logger
{
public:
    static void log(const char *msg, const char *func, const QVector<QVariant> &args);
};

#endif // LOGGER_HPP
