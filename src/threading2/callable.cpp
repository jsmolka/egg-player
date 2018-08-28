#include "callable.hpp"

#include "threadpool.hpp"

Callable::Callable(QObject *parent)
    : ThreadedObject(parent)
    , m_thread(nullptr)
{
    setObjectsPerThread(s_objectsPerThread);
    moveToThread(ThreadPool::instance()->getSuitibleThread(*this));
}

Callable::~Callable()
{
    m_thread->setObjectCount(m_thread->objectCount() - 1);
}

void Callable::moveToThread(Thread *thread)
{
    m_thread = thread;

    connect(thread, &Thread::interrupted, this, &Callable::interrupt);
    connect(thread, &Thread::finished, this, &Callable::moveToMainThread);

    QObject::moveToThread(thread);
    thread->setObjectCount(thread->objectCount() + 1);

    if (!thread->isRunning())
        thread->start();
}

void Callable::invoke(QObject *object, const char *method, QGenericArgument arg)
{
    QMetaObject::invokeMethod(object, method, arg);
}
