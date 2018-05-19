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
 * Gets the ideal thread count.
 *
 * :return: ideal thread count
 */
int ThreadPool::idealCount() const
{
    return QThread::idealThreadCount();
}

/*
 * Gets the current thread count.
 *
 * :return: current thread count
 */
int ThreadPool::currentCount() const
{
    return _count;
}

/*
 * Gets the advised thread count.
 *
 * :return: advised thread count
 */
int ThreadPool::advisedCount() const
{
    return idealCount() - currentCount();
}

/*
 * Adds a thread into the pool. Takes ownership.
 *
 * :param thread: thread
 */
void ThreadPool::add(AbstractThread *thread)
{
    thread->setParent(this);
    m_threads << thread;
    connect(thread, SIGNAL(finished()), this, SLOT(onThreadFinished()));
}

/*
 * Starts all threads.
 */
void ThreadPool::start()
{
    for (AbstractThread *thread : m_threads)
        if (!thread->isFinished())
            thread->start();
}

/*
 * Increments the amout of finished threads.
 *
 * :emit finished: all threads finished
 */
void ThreadPool::onThreadFinished()
{
    m_finished++;
    _count--;

    if (isFinished())
        emit finished();
}

/*
 * Current thread count.
 */
int ThreadPool::_count = 0;
