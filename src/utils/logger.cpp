#include "logger.hpp"

void log(const QString &message, const StringList &args)
{
    if (!cfgApp->log())
        return;

    QFile file(LOG_PATH);
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << LoggerPrivate::createLog(message, args) << "\n";
    }

#ifdef QT_DEBUG
    qDebug().noquote() << LoggerPrivate::createLog(message, args);
#endif
}

QString LoggerPrivate::createLog(QString message, const StringList &args)
{
    for (const QString &arg : args)
        message = message.arg(arg);

    QString time = QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss");
    return QString("[%1] %2").arg(time).arg(message);
}
