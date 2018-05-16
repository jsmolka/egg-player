#include "timer.hpp"

/*
 * Constructor.
 *
 * :param parent: parent, default nullptr
 */
Timer::Timer(QObject *parent) :
    QObject(parent)
{

}

/*
 * Constructor.
 *
 * :param interval: interval in milliseconds
 * :param parent: parent, default nullptr
 */
Timer::Timer(int interval, QObject *parent) :
    QObject(parent)
{
    pm_timer = new QTimer(this);
    pm_timer->setTimerType(Qt::PreciseTimer);

    m_elapsed = 0;
    m_interval = interval;
    m_remaining = m_interval;

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
 * Starts the timer using the remaining time. If
 * the remaining time is smaller than the
 * interval, it means that there is some time
 * left until the next timeout. After the next
 * timeout the remaining time will be equal to
 * to the interval again. Otherwise they are
 * equal which means that there is no remaining
 * time left.
 */
void Timer::start()
{
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
    m_elapsed = 0;
    m_remaining = m_interval;
    pm_timer->stop();
}

/*
 * Restarts the timer.
 */
void Timer::restart()
{
    stop();
    start();
}

/*
 * Set elapsed value of timer. The remaining
 * time get calculated and the timer starts
 * immediately if it was active.
 *
 * :param elapsed: elapsed
 */
void Timer::setElapsed(qint64 elapsed)
{
    m_elapsed = elapsed;
    m_remaining = elapsed % m_interval;

    if (m_remaining == 0)
        m_remaining = m_interval;
    if (pm_timer->isActive())
        start();
}

/*
 * Timer timeout event. Increments the elapsed
 * time and resets the remaining time to
 * interval.
 *
 * :emit timeout: elapsed
 */
void Timer::onTimeout()
{
    if (m_remaining != m_interval)
    {
        m_remaining = m_interval;
        start();
    }
    m_elapsed += m_interval;
    emit timeout(m_elapsed);
}
