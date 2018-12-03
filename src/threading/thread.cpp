#include "thread.hpp"

#include "core/logger.hpp"

Thread::Thread(QObject *parent)
    : QThread(parent)
    , m_objects(0)
    , m_maxObjects(0)
{

}

void Thread::incrementObjects()
{
    m_objects++;
}

void Thread::decrementObjects()
{
    if (--m_objects == 0)
    {
        quit();
        m_maxObjects = 0;
        emit emptied();
    }

}

bool Thread::isEmpty() const
{
    return m_objects == 0;
}

bool Thread::isFull() const
{
    return m_objects == m_maxObjects;
}

void Thread::interrupt()
{
    emit interrupted();
}

void Thread::waitToQuit()
{
    quit();

    if (wait(2500))
        return;

    egg_log() << "Could not stop thread within 2500 ms";
    terminate();
    wait();
}
