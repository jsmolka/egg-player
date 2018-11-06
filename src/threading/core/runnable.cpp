#include "runnable.hpp"

#include "threading/core/threadpool.hpp"

Runnable::Runnable()
    : m_thread(nullptr)
{
    moveToThread(egg_pool.getSuitibleThread(*this));
}

Runnable::~Runnable()
{
    m_thread->decrementObjects();
}

Thread *Runnable::thread()
{
    return m_thread;
}

int Runnable::objectsPerThread() const
{
    return 1;
}

void Runnable::run()
{
    m_thread->start();
}

void Runnable::moveToThread(Thread *thread)
{
    if (m_thread)
        disconnect(m_thread, nullptr, this, nullptr);

    m_thread = thread;

    connect(thread, &Thread::started, this, &Runnable::work);
    connect(this, &Runnable::finished, this, &Runnable::deleteLater);
    connect(thread, &Thread::interrupted, this, &Runnable::interrupt);

    QObject::moveToThread(thread);
    thread->incrementObjects();

    if (thread->maxObjects() == 0)
        thread->setMaxObjects(objectsPerThread());
}
