#include "abstractthread.hpp"

/*
 * Constructor. Connects the thread to the app so that it terminates cleanly
 * when it shots down. Also schedules the object for deletion once it finished
 * so that it does not have to be deleted manually (even though it should be).
 *
 * :param parent: parent
 */
AbstractThread::AbstractThread(QObject *parent) :
    QThread(parent),
    m_abort(false)
{
    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(abort()));
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
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
