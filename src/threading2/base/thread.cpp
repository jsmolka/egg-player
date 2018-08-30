#include "thread.hpp"

#include "logger.hpp"

Thread::Thread(QObject *parent)
    : QThread(parent)
    , m_objectCount(0)
    , m_maxObjectCount(0)
{
    m_timeout.setSingleShot(true);

    connect(this, &Thread::started, this, &Thread::onStarted);
    connect(&m_timeout, &QTimer::timeout, this, &Thread::onTimeout);
}

void Thread::setObjectCount(int count)
{
    m_objectCount = count;

    if (count == 0)
    {
        setMaxObjectCount(0);
        m_timeout.start(s_threadTimeout);
    }
}

int Thread::objectCount() const
{
    return m_objectCount;
}

void Thread::setMaxObjectCount(int count)
{
    m_maxObjectCount = count;
}

int Thread::maxObjectCount() const
{
    return m_maxObjectCount;
}

bool Thread::isEmpty() const
{
    return m_objectCount == 0;
}

bool Thread::isFull() const
{
    return m_objectCount == m_maxObjectCount;
}

void Thread::interrupt()
{
    emit interrupted();
}

void Thread::waitToQuit()
{
    quit();
    if (!wait(s_waitTimeout))
    {
        LOG("Could not stop thread within %1 ms", s_waitTimeout);
        terminate();
        wait();
    }
}

void Thread::onStarted()
{
    m_timeout.moveToThread(this);
}

void Thread::onTimeout()
{
    if (m_objectCount == 0)
    {
        waitToQuit();
        deleteLater();
    }
}
