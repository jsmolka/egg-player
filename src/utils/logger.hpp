#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <QApplication>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QStringList>
#include <QTextStream>

#include "config.hpp"
#include "constants.hpp"

class Logger
{
public:
    static void log(const QString &message, const QStringList &args = {});

private:    
    static QString createLog(QString message, const QStringList &args);

    static QFile * file();
    static QFile *_file;
};

#endif // LOGGER_HPP
