#include "logger.hpp"

/*
 * Creates and clears logger file.
 */
void Logger::create()
{
    if (file)
        return;

    file = new QFile(LOG_PATH, QApplication::instance());
    file->open(QIODevice::Append | QIODevice::Text);
    file->resize(0);
}

/*
 * Logs a message with two possible args. Also
 * writes the message into the console if Qt is
 * in debug mode.
 *
 * :param message: message
 * :param arg1: first arg
 * :param arg2: seconds arg
 */
void Logger::log(const QString &message, const QString &arg1, const QString &arg2)
{
    if (!Config::ALog())
        return;

    QString log = message;

    if (!arg1.isEmpty())
        log = log.arg(arg1);
    if (!arg2.isEmpty())
        log = log.arg(arg2);

    QString dateTime = QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss");
    QString text = QString("[%1] %2").arg(dateTime).arg(log);

#ifdef QT_DEBUG
    qDebug().noquote() << text;
#endif

    QTextStream out(file);
    out.setCodec("UTF-8");
    out << text << "\n";
    out.flush();
}

/*
 * File used for logging.
 */
QFile * Logger::file = nullptr;
