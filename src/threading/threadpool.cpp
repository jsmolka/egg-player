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
    return !isFinished();
}

int ThreadPool::activeCount()
{
    return _count;
}

int ThreadPool::idealCount()
{
    return QThread::idealThreadCount();
}

int ThreadPool::advisedCount()
{
    return idealCount() - activeCount();
}

int ThreadPool::count() const
{
    return m_threads.size();
}

AbstractThread * ThreadPool::threadAt(int index)
{
    AbstractThread *thread = nullptr;

    if (index > -1 && index < m_threads.size())
        thread = m_threads[index];

    return thread;
}

int ThreadPool::add(AbstractThread *thread)
{
    thread->setParent(this);
    connect(thread, SIGNAL(finished()), this, SLOT(onThreadFinished()));

    m_threads << thread;
    _count++;

    return m_threads.size() - 1;
}

void ThreadPool::start(int index)
{
    if (index == -1)
        startAll();
    else
        startAt(index);
}

void ThreadPool::abort(int index)
{
    if (index == -1)
        abortAll();
    else
        abortAt(index);
}

void ThreadPool::onThreadFinished()
{
    _count--;
    m_finished++;
    if (m_finished == m_threads.size())
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
    AbstractThread *thread = threadAt(index);
    if (thread && !thread->isRunning())
        thread->start();
}

void ThreadPool::abortAll()
{
    for (AbstractThread *thread : m_threads)
        thread->abort();
}

void ThreadPool::abortAt(int index)
{
    AbstractThread *thread = threadAt(index);
    if (thread && !thread->isRunning())
        thread->abort();
}

int ThreadPool::_count = 0;
