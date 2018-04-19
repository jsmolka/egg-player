#include "timer.hpp"

Timer::Timer(int interval, QObject *parent) : QObject(parent)
{
    pm_timer = new QTimer(parent);
    pm_timer->setTimerType(Qt::PreciseTimer);
    m_interval = interval;
    m_total = 0;
    m_remaining = m_interval;

    connect(pm_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

Timer::~Timer()
{

}

int Timer::interval() const
{
    return m_interval;
}

qint64 Timer::total() const
{
    return m_total;
}

int Timer::remaining() const
{
    return m_remaining;
}

void Timer::start()
{
    // The remaining time is either equal to the interval or it is smaller
    // which means that the timer has been paused and there is a smaller time
    // span to the next timeout than the interval. After the next timeout the
    // remaining time will be equal to the inteval again.
    pm_timer->start(m_remaining);
}

void Timer::pause()
{
    m_remaining = pm_timer->remainingTime();
    pm_timer->stop();
}

void Timer::stop()
{
    m_total = 0;
    m_remaining = m_interval;
    pm_timer->stop();
}

void Timer::restart()
{
    stop();
    start();
}

void Timer::setTotal(qint64 total)
{
    m_total = total;
    m_remaining = total % m_interval;

    if (m_remaining == 0)
        m_remaining = m_interval;
    if (pm_timer->isActive())
        start();
}

void Timer::onTimeout()
{
    if (m_remaining != m_interval)
    {
        m_remaining = m_interval;
        start();
    }
    m_total += m_interval;
    emit timeout(m_total);
}
