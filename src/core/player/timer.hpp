#ifndef TIMER_HPP
#define TIMER_HPP

#include <QTimer>
#include <QObject>

/*
 * The Timer class is a pausable QTimer
 * implementation.
 */
class Timer : public QObject
{
    Q_OBJECT

public:
    Timer(int interval, QObject *parent = nullptr);
    ~Timer();

    qint64 elapsed() const;
    int interval() const;
    int remaining() const;

    void start();
    void pause();
    void stop();
    void restart();

public slots:
    void setElapsed(qint64 elapsed);

signals:
    void timeout(qint64);

private slots:
    void onTimeout();

private:
    QTimer *pm_timer;
    qint64 m_elapsed;
    int m_interval;
    int m_remaining;
};

#endif // TIMER_HPP
