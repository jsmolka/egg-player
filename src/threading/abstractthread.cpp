#include "abstractthread.hpp"

/*
 * Constructor. It is advised to use classes derived from this one in
 * combination with a thread pool because it manages their life time.
 *
 * :param parent: parent, default nullptr
 */
AbstractThread::AbstractThread(QObject *parent) :
    QThread(parent),
    m_abort(false)
{

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
 * Aborts the thread. The abort property gets sets to true which indicates that
 * the thread should be stopped. The abort property need to be checked inside
 * the event loop so that the thread can return at any given time.
 */
void AbstractThread::abort()
{
    m_abort = true;
    quit();
    wait();
}
