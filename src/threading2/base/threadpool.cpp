#include "threadpool.hpp"

#include <QApplication>

ThreadPool::ThreadPool(QObject *parent)
    : QObject(parent)
{

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

void ThreadPool::onThreadDestroyed(QObject *object)
{
    for (auto iter = m_threads.begin(); iter != m_threads.end(); ++iter)
    {
        if (*iter == object)
        {
            m_threads.erase(iter);
            return;
        }
    }
}

Thread *ThreadPool::createThread()
{
    Thread *thread = new Thread;
    connect(thread, &Thread::destroyed, this, &ThreadPool::onThreadDestroyed);
    m_threads << thread;
    return thread;
}
