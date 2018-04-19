#include "logger.hpp"

QFile *file = nullptr;

void Logger::create()
{
    if (!file)
    {
        // Open and clear file
        file = new QFile(LOG_PATH, QApplication::instance());
        file->open(QIODevice::Append | QIODevice::Text);
        file->resize(0);
    }
}

void Logger::log(const QString &message, const QString &arg1, const QString &arg2)
{
    if (Config::log())
    {
        QString argMessage;

        if (!arg1.isEmpty())
            argMessage = message.arg(arg1);
        if (!arg2.isEmpty())
            argMessage = argMessage.arg(arg2);

        QString dateTime = QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss");
        QString text = QString("[%1] %2\n").arg(dateTime).arg(argMessage);

        QTextStream out(file);
        out.setCodec("UTF-8");
        out << text;
        out.flush();
    }
}
