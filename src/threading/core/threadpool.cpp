#include "threadpool.hpp"

Thread *ThreadPool::suitibleThread(const ThreadObject &object)
{
    for (ExpiringThread *expiring : qAsConst(m_threads))
    {
        Thread *thread = expiring->thread();
        if (thread->isEmpty())
            return thread;

        if (thread->maxObjects() == object.objectsPerThread()
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
    const int index = m_threads.indexOf(thread);
    if (index != -1)
        m_threads.remove(index);
}

ExpiringThread *ThreadPool::createThread()
{
    ExpiringThread *thread = new ExpiringThread(this);
    connect(thread, &ExpiringThread::expired, this, &ThreadPool::onThreadExpired);
    m_threads << thread;

    return thread;
}
