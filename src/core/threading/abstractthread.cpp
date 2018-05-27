#include "abstractthread.hpp"

/*
 * Constructor.
 *
 * :param parent: parent, default nullptr
 */
AbstractThread::AbstractThread(QObject *parent) :
    QThread(parent),
    m_abort(false)
{
    connect(this, SIGNAL(started()), this, SLOT(onStarted()));
}

/*
 * Destructor. Exits the thread if it is still running.
 */
AbstractThread::~AbstractThread()
{
    if (isRunning())
        abort();
}

/*
 * Getter for abort property.
 *
 * :return: abort
 */
bool AbstractThread::isAbort() const
{
    return m_abort;
}

/*
 * Resets the abort property at every start.
 */
void AbstractThread::onStarted()
{
    m_abort = false;
}

/*
 * Aborts the thread. The abort property gets sets to true which indicates that
 * the thread should be stopped. The abort property need to be checked inside
 * the event loop so that the thread can return at any given time.
 */
void AbstractThread::abort()
{
    m_abort = true;

    if (!wait(5000))
    {
        Logger::log("AbstractThread: Could not abort within 5 seconds");
        terminate();
    }
}
