#include "logger.hpp"

QString createLog(QString message, const QVector<QVariant> &args)
{
    for (const QVariant &arg : args)
        message = message.arg(arg.toString());

    QString time = QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss");
    return QString("[%1] %2").arg(time).arg(message);
}

void log(const QString &message, const QVector<QVariant> &args)
{
    if (!cfgApp->log())
        return;

    QFile file(LOG_PATH);
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << createLog(message, args) << "\n";
    }

    qDebug().noquote() << createLog(message, args);
}
