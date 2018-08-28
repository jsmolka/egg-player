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
    for (Thread *thread : qAsConst(m_threads))
    {
        if (thread->objectCount() == 0)
            return thread;

        if (thread->isShared() && thread->objectCount() < object.objectsPerThread())
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

Thread *ThreadPool::createThread()
{
    Thread *thread = new Thread;
    m_threads << thread;
    return thread;
}
