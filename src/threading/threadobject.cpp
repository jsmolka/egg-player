#include "threadobject.hpp"

#include <QApplication>

ThreadObject::ThreadObject()
    : m_interrupted(false)
{

}

bool ThreadObject::isInterrupted() const
{
    QCoreApplication::processEvents();

    return m_interrupted;
}

void ThreadObject::interrupt()
{
    m_interrupted = true;
}

void ThreadObject::moveToMainThread()
{
    QObject::moveToThread(qApp->thread());
}
