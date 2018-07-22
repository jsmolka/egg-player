#include "abstractthread.hpp"

AbstractThread::AbstractThread(QObject *parent)
    : QThread(parent)
    , m_interrupt(false)
{
    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(deleteLater()));

    connect(this, SIGNAL(started()), this, SLOT(onStarted()));
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
}

AbstractThread::~AbstractThread()
{
    if (isRunning())
        interrupt();
}

bool AbstractThread::isInterrupt() const
{
    return m_interrupt;
}

void AbstractThread::onStarted()
{
    m_interrupt = false;
}

void AbstractThread::interrupt()
{
    m_interrupt = true;

    if (!wait(5000))
    {
        log("AbstractThread: Could not interrupt within 5 seconds");
        terminate();
        deleteLater();
    }
}
