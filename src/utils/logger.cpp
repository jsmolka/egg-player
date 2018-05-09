#include "logger.hpp"

/*
 * Logs a message with args. Also writes the
 * message into the console if Qt is in debug
 * mode.
 *
 * :param message: message
 * :param args: arguments, default empty
 */
void Logger::log(const QString &message, const QStringList &args)
{
    if (!Config::App::log())
        return;

    if (!file)
        Logger::createAndClearFile();

    if (file->open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(file);
        out.setCodec("UTF-8");
        out << createLog(message, args) << "\n";
        file->close();
    }

#ifdef QT_DEBUG
    qDebug().noquote() << createLog(message, args);
#endif
}

/*
 * Creates and clears log file.
 */
void Logger::createAndClearFile()
{
    file = new QFile(LOG_PATH, qApp);
    file->open(QIODevice::Append | QIODevice::Text);
    file->resize(0);
    file->close();
}

/*
 * Creates log message.
 *
 * :param message: message
 * :param args: args
 * :return: log message
 */
QString Logger::createLog(const QString &message, const QStringList &args)
{
    QString log = message;
    for (const QString &arg : args)
        log = log.arg(arg);

    QString time = QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss");
    return QString("[%1] %2").arg(time).arg(log);
}

/*
 * File used for logging.
 */
QFile * Logger::file = nullptr;
