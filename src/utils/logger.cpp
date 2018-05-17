#include "logger.hpp"

/*
 * Logs a message with args.
 *
 * :param message: message
 * :param args: args, default empty
 */
void Logger::log(const QString &message, const QStringList &args)
{
    if (!Config::App::log())
        return;

    if (file()->open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(file());
        out.setCodec("UTF-8");
        out << createLog(message, args) << "\n";
        file()->close();
    }

#ifdef QT_DEBUG
    qDebug().noquote() << createLog(message, args);
#endif
}

/*
 * Creates a log message.
 *
 * :param message: message
 * :param args: args
 * :return: log message
 */
QString Logger::createLog(QString message, const QStringList &args)
{
    for (const QString &arg : args)
        message = message.arg(arg);

    QString time = QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss");
    return QString("[%1] %2").arg(time).arg(message);
}

/*
 * Gets or creates file instance.
 *
 * :return: file
 */
QFile * Logger::file()
{
    if (!_file)
        _file = new QFile(LOG_PATH, qApp);

    return _file;
}

/*
 * File used for logging.
 */
QFile * Logger::_file = nullptr;
