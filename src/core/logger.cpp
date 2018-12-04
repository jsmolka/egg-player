#include "logger.hpp"

#include <QDateTime>
#include <QDebug>
#include <QMutex>
#include <QMutexLocker>

#include "core/constants.hpp"

Logger::Logger(const char *function)
{
    const QString time = QDateTime::currentDateTime().toString("dd-MM-yy hh:mm");

    m_strings << QString("[%1]").arg(time);
    m_strings << QString("%1:").arg(function);
}

Logger::~Logger()
{
    const QString message = m_strings.join(" ");

    static QMutex mutex;
    QMutexLocker locker(&mutex);

    auto &stream = textStream();
    stream << message << "\n";
    stream.flush();

    qDebug().noquote() << message;
}

Logger &Logger::operator<<(const QString &string)
{
    m_strings << string;

    return *this;
}

Logger &Logger::operator<<(int value)
{
    return *this << QString::number(value);
}

QFile &Logger::file()
{
    static QFile file(constants::log::File);
    if (!file.isOpen())
        file.open(QFile::Append);

    return file;
}

QTextStream &Logger::textStream()
{
    static QTextStream stream(&file());

    return stream;
}
