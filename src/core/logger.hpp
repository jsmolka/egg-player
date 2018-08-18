#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <QString>
#include <QVector>
#include <QVariant>

#define LOG(message, ...)                                               \
    do {                                                                \
        Logger::log(message, __FUNCTION__, {__VA_ARGS__});     \
    } while (0)

namespace Logger
{
    extern void log(const QString &message, const char *function, const QVector<QVariant> &args);
}



#endif // LOGGER_HPP
