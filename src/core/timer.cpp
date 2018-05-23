#include "timer.hpp"

/*
 * Constructor.
 *
 * :param interval: interval in milliseconds
 * :param parent: parent, default nullptr
 */
Timer::Timer(int interval, QObject *parent) :
    QObject(parent),
    pm_timer(new QTimer(this)),
    m_elapsed(0),
    m_max(0),
    m_interval(interval),
    m_remaining(interval)
{
    pm_timer->setTimerType(Qt::PreciseTimer);

    connect(pm_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

/*
 * Destructor.
 */
Timer::~Timer()
{

}

/*
 * Getter for elapsed property.
 *
 * :return: elapsed
 */
qint64 Timer::elapsed() const
{
    return m_elapsed;
}

/*
 * Getter for interval property.
 *
 * :return: interval
 */
int Timer::interval() const
{
    return m_interval;
}

/*
 * Getter for remaining property.
 *
 * :return: remaining
 */
int Timer::remaining() const
{
    return m_remaining;
}

/*
 * Starts the timer using the remaining time. It uses the remaining time to
 * always emit a timeout at multiple of interval. If the timer gets stopped
 * the remaining time will be used to bridge the time till the next interval.
 *
 * :param max: max in milliseconds
 */
void Timer::start(qint64 max)
{
    m_max = max;
    pm_timer->start(m_remaining);
}

/*
 * Stop the timer and sets the remaining time.
 */
void Timer::pause()
{
    m_remaining = pm_timer->remainingTime();
    pm_timer->stop();
}

/*
 * Stops the timer
 */
void Timer::stop()
{
    pm_timer->stop();
    m_elapsed = 0;
    m_max = 0;
    m_remaining = m_interval;
}

/*
 * Restarts the timer.
 *
 * :param max: max in milliseconds
 */
void Timer::restart(qint64 max)
{
    stop();
    start(max);
}

/*
 * Set elapsed value of timer. The remaining time gets calculated and the timer
 * starts immediately if it was active.
 *
 * :param elapsed: elapsed
 */
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

/*
 * Increments the elapsed time and resets the remaining time to interval.
 *
 * :emit timeout: elapsed
 */
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
