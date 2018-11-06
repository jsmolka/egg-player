#include "logger.hpp"

#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "core/constants.hpp"
#include "core/config/config.hpp"

void Logger::log(const char *msg, const char *func, const QVector<QVariant> &args)
{
    if (!cfg_app.log())
        return;

    QString message(msg);
    QString function(func);

    for (const QVariant &arg : args)
    {
        if (arg.canConvert(QVariant::String))
            message = message.arg(arg.toString());
    }

    const QString time = QDateTime::currentDateTime().toString("dd-MM-yy hh:mm");
    message = QString("[%1] %2: %3").arg(time, function, message);

    QFile file(constants::log::file);
    if (file.open(QIODevice::Append))
    {
        QTextStream stream(&file);
        stream << message << "\n";
    }
    qDebug().noquote() << message;
}
