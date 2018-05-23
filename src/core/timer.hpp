#ifndef TIMER_HPP
#define TIMER_HPP

#include <QTimer>
#include <QObject>

class Timer : public QObject
{
    Q_OBJECT

public:
    Timer(int interval, QObject *parent = nullptr);
    ~Timer();

    qint64 elapsed() const;
    int interval() const;
    int remaining() const;

    void start(qint64 max);
    void pause();
    void stop();
    void restart(qint64 max);

public slots:
    void setElapsed(qint64 elapsed);

signals:
    void timeout(qint64);
    void finished();

private slots:
    void onTimeout();

private:
    QTimer *pm_timer;
    qint64 m_elapsed;
    qint64 m_max;
    int m_interval;
    int m_remaining;
};

#endif // TIMER_HPP
