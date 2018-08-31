#include "expiringthread.hpp"

#include <QApplication>

#include <QDebug>

ExpiringThread::ExpiringThread(QObject *parent)
    : QObject(parent)
    , m_thread(new Thread)
    , m_timer(this)
    , m_quitting(false)
{
    connect(m_thread, &Thread::emptied, this, &ExpiringThread::onEmptied);
    connect(&m_timer, &QTimer::timeout, this, &ExpiringThread::onTimeout);
    connect(qApp, &QApplication::aboutToQuit, this, &ExpiringThread::onAppQuitting);

    m_timer.setSingleShot(true);
}

Thread *ExpiringThread::thread() const
{
    return m_thread;
}

void ExpiringThread::onTimeout()
{
    if (m_thread->isEmpty())
    {
        m_thread->waitToQuit();
        m_thread->deleteLater();
        emit expired(this);
    }
}

void ExpiringThread::onAppQuitting()
{
    m_quitting = true;
}

void ExpiringThread::onEmptied()
{
    if (!m_quitting)
        m_timer.start(s_timeout);
}
