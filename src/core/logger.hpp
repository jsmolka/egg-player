#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>

#define egg_log() Logger(__FUNCTION__)

class Logger
{
public:
    Logger(const char *function);
    ~Logger();

    Logger &operator<<(const QString &string);
    Logger &operator<<(int value);

private:
    static QFile &file();
    static QTextStream &fileStream();

    QStringList m_strings;
};

#endif // LOGGER_HPP
