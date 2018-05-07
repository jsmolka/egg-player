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

    QString log = message;
    for (const QString &arg : args)
        log = log.arg(arg);

    QString time = QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss");
    QString text = QString("[%1] %2").arg(time).arg(log);

    if (!file)
        Logger::createAndClear();

    file->open(QIODevice::Append | QIODevice::Text);
    QTextStream out(file);
    out.setCodec("UTF-8");
    out << text << "\n";
    file->close();

#ifdef QT_DEBUG
    qDebug().noquote() << text;
#endif
}

/*
 * Creates and clears log file.
 */
void Logger::createAndClear()
{
    file = new QFile(LOG_PATH, qApp);
    file->open(QIODevice::Append | QIODevice::Text);
    file->resize(0);
    file->close();
}

/*
 * File used for logging.
 */
QFile * Logger::file = nullptr;
