#include "logger.hpp"

QString createLog(QString message, const QVector<QVariant> &args)
{
    for (const QVariant &arg : args)
        message = message.arg(arg.toString());

    QString time = QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss");
    return QString("[%1] %2").arg(time).arg(message);
}

void logArgs(const QString &message, const QVector<QVariant> &args)
{
    QFile file(LOG_PATH);
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << createLog(message, args) << "\n";
    }
    qDebug().noquote() << createLog(message, args);
}

void log(const QString &message,
         const QVariant &arg1,
         const QVariant &arg2,
         const QVariant &arg3,
         const QVariant &arg4)
{
    if (!cfgApp->log())
        return;

    QVector<QVariant> args;
    if (!arg1.isNull()) args << arg1;
    if (!arg2.isNull()) args << arg2;
    if (!arg3.isNull()) args << arg3;
    if (!arg4.isNull()) args << arg4;

    logArgs(message, args);
}
