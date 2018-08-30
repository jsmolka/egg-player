#include "thread.hpp"

#include "logger.hpp"

Thread::Thread(QObject *parent)
    : QThread(parent)
    , m_objectCount(0)
    , m_maxObjectCount(0)
{

}

void Thread::setObjectCount(int count)
{
    m_objectCount = count;

    if (count == 0)
    {
        quit();
        setMaxObjectCount(0);
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
    if (!wait(s_timeout))
    {
        LOG("Could not stop thread within %1 ms", s_timeout);
        terminate();
        wait();
    }
}
