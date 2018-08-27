#include "threadedobject.hpp"

#include <QApplication>

ThreadedObject::ThreadedObject(QObject *parent)
    : QObject(parent)
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

void ThreadedObject::moveToMainThread()
{
    this->QObject::moveToThread(qApp->thread());
}
