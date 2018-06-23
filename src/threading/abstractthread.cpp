#include "abstractthread.hpp"

AbstractThread::AbstractThread(QObject *parent)
    : QThread(parent)
    , m_abort(false)
{
    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(deleteLater()));

    connect(this, SIGNAL(started()), this, SLOT(onStarted()));
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
    connect(this, SIGNAL(terminated()), this, SLOT(deleteLater()));
}

AbstractThread::~AbstractThread()
{
    if (isRunning())
        abort();
}

bool AbstractThread::isAbort() const
{
    return m_abort;
}

void AbstractThread::onStarted()
{
    m_abort = false;
}

void AbstractThread::abort()
{
    m_abort = true;

    if (!wait(5000))
    {
        log("AbstractThread: Could not abort within 5 seconds");
        terminate();
        emit terminated();
    }
}
