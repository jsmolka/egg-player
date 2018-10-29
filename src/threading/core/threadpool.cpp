#include "threadpool.hpp"

ThreadPool::ThreadPool(QObject *parent)
    : QObject(parent)
{

}

ThreadPool &ThreadPool::instance()
{
    static ThreadPool pool;

    return pool;
}

Thread *ThreadPool::getSuitibleThread(ThreadObject *object)
{
    for (ExpiringThread *expiring : qAsConst(m_threads))
    {
        Thread *thread = expiring->thread();
        if (thread->isEmpty())
            return thread;

        if (thread->maxObjects() == object->objectsPerThread()
                && !thread->isFull())
            return thread;
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
            return;
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
