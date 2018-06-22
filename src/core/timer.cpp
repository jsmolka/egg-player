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

bool Timer::isActive() const
{
    return pm_timer->isActive();
}

void Timer::start(qint64 max)
{
    m_max = max;

    if (m_remaining > -1)
    {
        pm_timer->start(m_remaining);
    }
    else
    {
        log("Timer: Negative remaining time %1", {m_remaining});
        finish();
    }
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
    qint64 remaining = m_max - elapsed;
    if (remaining < 0)
    {
        log("Timer: Invalid elapsed time %1 for max %2", {elapsed, m_max});
        return;
    }

    m_elapsed = elapsed;

    if (remaining < m_interval)
        m_remaining = remaining;
    else
        m_remaining = elapsed % m_interval;

    if (m_remaining == 0)
        m_remaining = m_interval;

    if (pm_timer->isActive())
        start(m_max);
}

void Timer::onTimeout()
{
    if (m_elapsed + m_interval >= m_max)
    {
        finish();
        return;
    }

    m_elapsed += m_interval;
    emit timeout(m_elapsed);

    qint64 remaining = m_max - m_elapsed;
    if (remaining < m_interval)
    {
        m_remaining = remaining;
        start(m_max);
    }
    else
    {
        if (m_remaining != m_interval)
        {
            m_remaining = m_interval;
            start(m_max);
        }
    }
}

void Timer::finish()
{
    stop();
    emit finished();
}
