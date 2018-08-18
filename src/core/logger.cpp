#include "logger.hpp"

#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "config.hpp"
#include "constants.hpp"

void Logger::log(const QString &message, const char *function, const QVector<QVariant> &args)
{
    if (!cfgApp->log())
        return;

    QString logMessage = message;
    for (const QVariant &arg : args)
    {
        if (!arg.isNull())
            logMessage = logMessage.arg(arg.toString());
    }
    const QString timeStamp = QDateTime::currentDateTime().toString("dd-MM-yy hh:mm");
    logMessage = QString("[%1] %2: %3").arg(timeStamp).arg(function).arg(logMessage);

    QFile file(LOG_PATH);
    if (file.open(QIODevice::Append))
    {
        QTextStream stream(&file);
        stream << logMessage << "\n";
    }
    qDebug().noquote() << logMessage;
}
