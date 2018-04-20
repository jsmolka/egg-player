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

    int interval() const;
    qint64 total() const;
    int remaining() const;

    void start();
    void pause();
    void stop();
    void restart();

public slots:
    void setTotal(qint64 total);

signals:
    void timeout(qint64);

private slots:
    void onTimeout();

private:
    QTimer *pm_timer;
    int m_interval;
    qint64 m_total;
    int m_remaining;
};

#endif // TIMER_HPP