#include "thread.hpp"

#include "logger.hpp"

Thread::Thread(QObject *parent)
    : QThread(parent)
    , m_shared(true)
    , m_objectCount(0)
{

}

void Thread::setShared(bool shared)
{
    m_shared = shared;
}

bool Thread::isShared() const
{
    return m_shared;
}

void Thread::setObjectCount(int count)
{
    m_objectCount = count;
}

int Thread::objectCount() const
{
    return m_objectCount;
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
