#include "threadpool.hpp"

ThreadPool::ThreadPool(QObject *parent)
    : QObject(parent)
    , m_finished(0)
{

}

ThreadPool::~ThreadPool()
{

}

bool ThreadPool::isFinished() const
{
    return m_finished == m_threads.size();
}

bool ThreadPool::isRunning() const
{
    for (AbstractThread *thread : m_threads)
        if (thread->isRunning())
            return true;

    return false;
}

int ThreadPool::current(bool global) const
{
    return global ? _count : m_threads.size();
}

int ThreadPool::ideal() const
{
    return QThread::idealThreadCount();
}

int ThreadPool::advised() const
{
    return ideal() - current(true);
}

int ThreadPool::add(AbstractThread *thread)
{
    thread->setParent(this);
    m_threads << thread;
    connect(thread, SIGNAL(finished()), this, SLOT(onThreadFinished()));

    if (++_count > ideal())
        log("ThreadPool: Thread count exceeded ideal count");

    return m_threads.size() - 1;
}

void ThreadPool::start(int index)
{
    if (index == -1)
        startAll();
    else
        startAt(index);
}

void ThreadPool::onThreadFinished()
{
    _count--;
    if (++m_finished == m_threads.size())
        emit finished();
}

void ThreadPool::startAll()
{
    for (AbstractThread *thread : m_threads)
        if (!thread->isFinished())
            thread->start();
}

void ThreadPool::startAt(int index)
{
    AbstractThread *thread = m_threads[index];
    if (!thread->isRunning())
        thread->start();
}

int ThreadPool::_count = 0;
