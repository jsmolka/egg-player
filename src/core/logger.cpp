#include "logger.hpp"

#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "core/constants.hpp"
#include "core/config/config.hpp"

void Logger::log(const QString &message, const QString &func, const QVector<QVariant> &args)
{
    if (!cfgApp.log())
        return;

    QString edited = message;
    for (const QVariant &arg : args)
         edited = edited.arg(arg.toString());

    const QString time = QDateTime::currentDateTime().toString("dd-MM-yy hh:mm");
    edited = QString("[%1] %2: %3").arg(time, func, edited);

    QFile file(constants::log::file);
    if (file.open(QIODevice::Append))
    {
        QTextStream stream(&file);
        stream << edited << "\n";
    }
    qDebug().noquote() << edited;
}
