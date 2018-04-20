#include "timer.hpp"

/*
 * Constructor.
 *
 * :param interval: interval in milliseconds
 * :param parent: parent object pointer
 */
Timer::Timer(int interval, QObject *parent) : QObject(parent)
{
    pm_timer = new QTimer(parent);
    pm_timer->setTimerType(Qt::PreciseTimer);
    m_interval = interval;
    m_total = 0;
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
 * Getter for interval property.
 *
 * :return: interval
 */
int Timer::interval() const
{
    return m_interval;
}

/*
 * Getter for total time property.
 *
 * :return: total elapsed time
 */
qint64 Timer::total() const
{
    return m_total;
}

/*
 * Getter for remaining time property.
 *
 * :return: remaining time
 */
int Timer::remaining() const
{
    return m_remaining;
}

/*
 * Starts the timer using the remaining time. This one is either smaller
 * than the interval which means that there is remaining time left. After
 * the next timeout the remaining time is equal to the interval again.
 * Otherwise they are equal which means that there is no remaining time
 * left.
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
    m_total = 0;
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
 * Set total value of timer. The remaining
 * time get calculated and the timer starts
 * immediately if it was active.
 *
 * :param total: new total
 */
void Timer::setTotal(qint64 total)
{
    m_total = total;
    m_remaining = total % m_interval;

    if (m_remaining == 0)
        m_remaining = m_interval;
    if (pm_timer->isActive())
        start();
}

/*
 * Slot for timer timeout. It increments
 * the total time and resets the remaining
 * time to interval time.
 */
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
