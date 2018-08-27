#include "callable.hpp"

Callable::Callable(QObject *parent)
    : ThreadedObject(parent)
{
    setObjectsPerThread(8);
}

void Callable::moveToThread(Thread *thread)
{
    connect(thread, &Thread::finished, this, &ThreadedObject::moveToMainThread);

    this->QObject::moveToThread(thread);
}
