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

void Logger::log(const QString &message)
{
    if (Config::log())
    {
        QString dateTime = QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss");
        QString text = QString("[%1] %2\n").arg(dateTime).arg(message);

        QTextStream out(file);
        out.setCodec("UTF-8");
        out << text;
        out.flush();
    }
}
