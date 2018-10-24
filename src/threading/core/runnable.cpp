#include "runnable.hpp"

#include "threading/core/threadpool.hpp"

Runnable::Runnable(QObject *parent)
    : ThreadedObject(parent)
    , m_thread(nullptr)
{
    setObjectsPerThread(s_objectsPerThread);
    moveToThread(ThreadPool::instance()->getSuitibleThread(*this));
}

Runnable::~Runnable()
{
    m_thread->setObjectCount(m_thread->objectCount() - 1);
}

Thread *Runnable::thread()
{
    return m_thread;
}

void Runnable::moveToThread(Thread *thread)
{
    m_thread = thread;

    connect(thread, &Thread::started, this, &Runnable::work);
    connect(this, &Runnable::finished, this, &Runnable::deleteLater);
    connect(thread, &Thread::interrupted, this, &Runnable::interrupt);

    QObject::moveToThread(thread);
    thread->setObjectCount(thread->objectCount() + 1);

    if (thread->maxObjectCount() == 0)
        thread->setMaxObjectCount(objectsPerThread());
}

void Runnable::run()
{
    m_thread->start();
}
