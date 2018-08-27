#include "thread.hpp"

Thread::Thread(QObject *parent)
    : QThread(parent)
    , m_shared(true)
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
