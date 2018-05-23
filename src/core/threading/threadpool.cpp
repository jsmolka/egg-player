#include "threadpool.hpp"

/*
 * Constructor.
 *
 * :param parent: parent
 */
ThreadPool::ThreadPool(QObject *parent) :
    QObject(parent),
    m_finished(0)
{

}

/*
 * Destructor.
 */
ThreadPool::~ThreadPool()
{

}

/*
 * Checks if all threads finished.
 *
 * :return: finished
 */
bool ThreadPool::isFinished() const
{
    return m_finished == m_threads.size();
}

/*
 * Checks if a thread is still running.
 *
 * :return: running
 */
bool ThreadPool::isRunning() const
{
    for (AbstractThread *thread : m_threads)
        if (thread->isRunning())
            return true;

    return false;
}

/*
 * Gets the current pool thread count.
 *
 * :param global: use global count, default false
 * :return: count
 */
int ThreadPool::current(bool global) const
{
    return global ? _count : m_threads.size();
}

/*
 * Gets the ideal thread count.
 *
 * :return: count
 */
int ThreadPool::ideal() const
{
    return QThread::idealThreadCount();
}

/*
 * Gets the advised thread count.
 *
 * :return: count
 */
int ThreadPool::advised() const
{
    return ideal() - current(true);
}

/*
 * Adds a thread into the pool. Takes ownership.
 *
 * :param thread: thread
 * :return: index
 */
int ThreadPool::add(AbstractThread *thread)
{
    thread->setParent(this);
    m_threads << thread;
    connect(thread, SIGNAL(finished()), this, SLOT(onThreadFinished()));

    if (++_count > ideal())
        Logger::log("ThreadPool: Thread count exceeded ideal count");

    return m_threads.size() - 1;
}

/*
 * Starts a thread if is has not finished yet. Starts all if -1.
 *
 * :param index: index, default -1
 */
void ThreadPool::start(int index)
{
    if (index == -1)
        startAll();
    else
        startAt(index);
}

/*
 * Increments the amout of finished threads.
 *
 * :emit finished: all threads finished
 */
void ThreadPool::onThreadFinished()
{
    _count--;
    if (++m_finished == m_threads.size())
        emit finished();
}

/*
 * Starts all threads if they have not finished yet.
 */
void ThreadPool::startAll()
{
    for (AbstractThread *thread : m_threads)
        if (!thread->isFinished())
            thread->start();
}

/*
 * Starts a thread at an index if it has not finished yet.
 *
 * :param index: index
 */
void ThreadPool::startAt(int index)
{
    AbstractThread *thread = m_threads[index];
    if (!thread->isRunning())
        thread->start();
}

/*
 * Global thread count.
 */
int ThreadPool::_count = 0;
