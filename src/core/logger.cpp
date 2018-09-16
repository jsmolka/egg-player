#include "logger.hpp"

#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "config.hpp"
#include "constants.hpp"

void Logger::log(const QString &message, const QString &func, const QVector<QVariant> &args)
{
    if (!cfgApp.log())
        return;

    QString final = message;
    for (const QVariant &arg : args)
    {
        if (!arg.isNull())
            final = final.arg(arg.toString());
    }
    const QString time = QDateTime::currentDateTime().toString("dd-MM-yy hh:mm");
    final = QString("[%1] %2: %3").arg(time, func, final);

    QFile file(LOG_PATH);
    if (file.open(QIODevice::Append))
    {
        QTextStream stream(&file);
        stream << final << "\n";
    }
    qDebug().noquote() << final;
}
