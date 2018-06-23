#ifndef TIMER_HPP
#define TIMER_HPP

#include <QTimer>
#include <QObject>

#include "logger.hpp"

class Timer : public QObject
{
    Q_OBJECT

public:
    Timer(int interval, QObject *parent = nullptr);
    ~Timer();

    qint64 elapsed() const;
    qint64 limit() const;
    int interval() const;
    int remaining() const;

    bool isActive() const;

    void start(qint64 limit);
    void pause();
    void stop();
    void restart(qint64 limit);

public slots:
    void setElapsed(qint64 elapsed);

signals:
    void timeout(qint64 elapsed);
    void finished();

private slots:
    void onTimeout();

private:
    void finish();

    QTimer *pm_timer;
    qint64 m_elapsed;
    qint64 m_limit;
    int m_interval;
    int m_remaining;
};

#endif // TIMER_HPP
