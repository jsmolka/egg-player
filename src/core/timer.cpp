#include "timer.hpp"

Timer::Timer(int interval, QObject *parent)
    : QObject(parent)
    , pm_timer(new QTimer(this))
    , m_elapsed(0)
    , m_max(0)
    , m_interval(interval)
    , m_remaining(interval)
{
    pm_timer->setTimerType(Qt::PreciseTimer);

    connect(pm_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

Timer::~Timer()
{

}

qint64 Timer::elapsed() const
{
    return m_elapsed;
}

int Timer::interval() const
{
    return m_interval;
}

int Timer::remaining() const
{
    return m_remaining;
}

void Timer::start(qint64 max)
{
    m_max = max;
    pm_timer->start(m_remaining);
}

void Timer::pause()
{
    m_remaining = pm_timer->remainingTime();
    pm_timer->stop();
}

void Timer::stop()
{
    pm_timer->stop();
    m_elapsed = 0;
    m_max = 0;
    m_remaining = m_interval;
}

void Timer::restart(qint64 max)
{
    stop();
    start(max);
}

void Timer::setElapsed(qint64 elapsed)
{
    qint64 temp = m_max - elapsed;
    if (temp < 0)
        return;

    m_elapsed = elapsed;

    if (temp < m_interval)
        m_remaining = temp;
    else
        m_remaining = elapsed % m_interval;

    if (m_remaining == 0)
        m_remaining = m_interval;
    if (pm_timer->isActive())
        pm_timer->start(m_remaining);
}

void Timer::onTimeout()
{
    if (m_elapsed + m_remaining == m_max)
    {
        stop();
        emit finished();
        return;
    }

    m_elapsed += m_interval;
    emit timeout(m_elapsed);

    qint64 temp = m_max - m_elapsed;
    if (temp < m_interval)
    {
        m_remaining = temp;
        pm_timer->start(m_remaining);
    }
    else
    {
        if (m_remaining != m_interval)
        {
            m_remaining = m_interval;
            pm_timer->start(m_remaining);
        }
    }
}
