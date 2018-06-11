#include "logger.hpp"

void Logger::log(const QString &message, const StringList &args)
{
    if (!Config::App::log())
        return;

    QFile file(LOG_PATH);
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << createLog(message, args) << "\n";
    }

#ifdef QT_DEBUG
    qDebug().noquote() << createLog(message, args);
#endif
}

QString Logger::createLog(QString message, const StringList &args)
{
    for (const QString &arg : args)
        message = message.arg(arg);

    QString time = QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss");
    return QString("[%1] %2").arg(time).arg(message);
}
