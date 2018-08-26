#include "thread.hpp"

Thread::Thread(QObject *parent)
    : QThread(parent)
    , m_shared(true)
    , m_objectsMax(0)
    , m_objectsCurrent(0)
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
