#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <QApplication>
#include <QDateTime>
#include <QFile>
#include <QStringList>
#include <QTextStream>

#ifdef QT_DEBUG
#include <QDebug>
#endif

#include "config.hpp"
#include "constants.hpp"

class Logger
{
public:
    static void create();

    static void log(const QString &message, const QStringList &args);
    static void log(const QString &message, const QString &arg1 = QString(), const QString &arg2 = QString());

private:
    static QFile *file;
};

#endif // LOGGER_HPP
