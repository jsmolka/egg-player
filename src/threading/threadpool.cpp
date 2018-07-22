#include "threadpool.hpp"

ThreadPool::ThreadPool(QObject *parent)
    : QObject(parent)
    , m_finished(0)
{

}

ThreadPool::~ThreadPool()
{
    abortAll();
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
    return qMax(1, idealCount() - activeCount());
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
    connect(thread, SIGNAL(finished()), this, SLOT(onThreadFinished()));

    m_threads << thread;
    ++_count;

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
    --_count;
    if (++m_finished == m_threads.size())
        emit finished();
}

void ThreadPool::startAll()
{
    for (int index = 0; index < m_threads.size(); ++index)
        startAt(index);
}

void ThreadPool::startAt(int index)
{
    AbstractThread *thread = threadAt(index);
    if (thread && !(thread->isRunning() || thread->isFinished()))
        thread->start();
}

void ThreadPool::abortAll()
{
    for (int index = 0; index < m_threads.size(); ++index)
        abortAt(index);
}

void ThreadPool::abortAt(int index)
{
    AbstractThread *thread = threadAt(index);
    if (thread && !thread->isFinished())
        thread->abort();
}

int ThreadPool::_count = 0;
