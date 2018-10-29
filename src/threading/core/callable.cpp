#include "callable.hpp"

#include "threading/core/threadpool.hpp"

Callable::Callable(QObject *parent)
    : ThreadObject(parent)
    , m_thread(nullptr)
{
    moveToThread(egg_pool.getSuitibleThread(this));
}

Callable::~Callable()
{
    m_thread->decrementObjects();
}

int Callable::objectsPerThread() const
{
    return 8;
}

void Callable::moveToThread(Thread *thread)
{
    if (m_thread)
        disconnect(m_thread, nullptr, this, nullptr);

    m_thread = thread;

    connect(thread, &Thread::interrupted, this, &Callable::interrupt);
    connect(thread, &Thread::finished, this, &Callable::moveToMainThread);

    QObject::moveToThread(thread);
    thread->incrementObjects();

    if (thread->maxObjects() == 0)
        thread->setMaxObjects(objectsPerThread());

    if (!thread->isRunning())
        thread->start();
}

void Callable::invoke(QObject *object, const char *method, QGenericArgument arg)
{
    QMetaObject::invokeMethod(object, method, arg);
}
