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
 * :return: index
 */
int ThreadPool::add(AbstractThread *thread)
{
    thread->setParent(this);
    m_threads << thread;
    connect(thread, SIGNAL(finished()), this, SLOT(onThreadFinished()));

    _count++;
    if (_count > idealCount())
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
    {
        for (AbstractThread *thread : m_threads)
            if (!thread->isFinished())
                thread->start();
    }
    else
    {
        if (!m_threads[index]->isFinished())
            m_threads[index]->start();
    }
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
