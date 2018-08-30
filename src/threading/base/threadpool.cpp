#include "threadpool.hpp"

#include <QApplication>

ThreadPool::ThreadPool(QObject *parent)
    : QObject(parent)
    , m_timer(this)
{
    connect(&m_timer, &QTimer::timeout, this, &ThreadPool::onTimeout);

    m_timer.start(s_timeout);
}

ThreadPool *ThreadPool::instance()
{
    static ThreadPool *pool = new ThreadPool(qApp);
    return pool;
}

QVector<Thread *> ThreadPool::threads() const
{
    return m_threads;
}

Thread *ThreadPool::getSuitibleThread(const ThreadedObject &object)
{
    for (Thread *thread : qAsConst(m_threads))
    {
        if (thread->isEmpty())
            return thread;

        if (thread->maxObjectCount() == object.objectsPerThread() && !thread->isFull())
            return thread;
    }
    return createThread();
}

void ThreadPool::interruptThreads()
{
    for (Thread *thread : qAsConst(m_threads))
        thread->interrupt();

    for (Thread *thread : qAsConst(m_threads))
        thread->waitToQuit();
}

void ThreadPool::onTimeout()
{
    auto iter = m_threads.begin();
    while (iter != m_threads.end())
    {
        Thread *thread = *iter;
        if (thread->isEmpty())
        {
            thread->waitToQuit();
            thread->deleteLater();
            iter = m_threads.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}

Thread *ThreadPool::createThread()
{
    Thread *thread = new Thread;
    m_threads << thread;
    return thread;
}
