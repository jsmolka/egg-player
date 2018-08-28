#include "threadedobject.hpp"

#include <QApplication>

ThreadedObject::ThreadedObject(QObject *parent)
    : QObject(parent)
    , m_objectsPerThread(0)
    , m_interrupted(false)
{

}

void ThreadedObject::setObjectsPerThread(int objects)
{
    m_objectsPerThread = objects;
}

int ThreadedObject::objectsPerThread() const
{
    return m_objectsPerThread;
}

bool ThreadedObject::isInterrupted() const
{
    QCoreApplication::processEvents();

    return m_interrupted;
}

void ThreadedObject::interrupt()
{
    m_interrupted = true;
}

void ThreadedObject::moveToMainThread()
{
    QObject::moveToThread(qApp->thread());
}
