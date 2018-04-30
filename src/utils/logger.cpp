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
 * Logs a message with args. Also writes the
 * message into the console if Qt is in debug
 * mode.
 *
 * :param message: message
 * :param args: arguments
 */
void Logger::log(const QString &message, const QStringList &args)
{
    if (!Config::App::log())
        return;

    QString log = message;

    for (const QString &arg : args)
        if (!arg.isNull())
            log = log.arg(arg);

    QString time = QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss");
    QString text = QString("[%1] %2").arg(time).arg(log);

    QTextStream out(file);
    out.setCodec("UTF-8");
    out << text << "\n";
    out.flush();

#ifdef QT_DEBUG
    qDebug().noquote() << text;
#endif
}

/*
 * Log wrapper.
 *
 * :param message: message
 * :param arg1: first argument
 * :param arg2: second argument
 */
void Logger::log(const QString &message, const QString &arg1, const QString &arg2)
{
    QStringList args;
    args << arg1;
    args << arg2;
    log(message, args);
}

/*
 * File used for logging.
 */
QFile * Logger::file = nullptr;
