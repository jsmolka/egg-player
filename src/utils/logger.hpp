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
    static void log(const QString &message, const QStringList &args = {});

private:
    static void createAndClearFile();

    static QFile *file;
};

#endif // LOGGER_HPP
