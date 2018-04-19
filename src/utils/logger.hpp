#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <QApplication>
#include <QDateTime>
#include <QFile>
#include <QTextStream>

#include "config.hpp"
#include "constants.hpp"

class Logger
{
public:
    static void create();
    static void log(const QString &message, const QString &arg1 = "", const QString &arg2 = "");
};

#endif // LOGGER_HPP
