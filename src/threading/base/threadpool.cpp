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

Thread *ThreadPool::getSuitibleThread(const ThreadedObject &object)
{
    for (ExpiringThread *thread : qAsConst(m_threads))
    {
        if (thread->thread()->isEmpty())
            return thread->thread();

        if (thread->thread()->maxObjectCount() == object.objectsPerThread()
                && !thread->thread()->isFull())
            return thread->thread();
    }
    return createThread()->thread();
}

void ThreadPool::interruptThreads()
{
    for (ExpiringThread *thread : qAsConst(m_threads))
        thread->thread()->interrupt();

    for (ExpiringThread *thread : qAsConst(m_threads))
        thread->thread()->waitToQuit();
}

void ThreadPool::onThreadExpired(ExpiringThread *thread)
{
    for (auto iter = m_threads.begin(); iter != m_threads.end(); ++iter)
    {
        if (*iter == thread)
        {
            m_threads.erase(iter);
            break;
        }
    }
}

ExpiringThread *ThreadPool::createThread()
{
    ExpiringThread *thread = new ExpiringThread(this);
    connect(thread, &ExpiringThread::expired, this, &ThreadPool::onThreadExpired);
    m_threads << thread;
    return thread;
}
