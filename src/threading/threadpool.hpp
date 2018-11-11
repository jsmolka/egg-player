#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <QVector>

#include "core/singleton.hpp"
#include "threading/expiringthread.hpp"
#include "threading/threadobject.hpp"

#define egg_pool (ThreadPool::instance())

class ThreadPool : public QObject, public Singleton<ThreadPool>
{
    Q_OBJECT

public:
    using QObject::QObject;

    Thread *suitibleThread(const ThreadObject &object);

    void interruptThreads();

private slots:
    void onThreadExpired(ExpiringThread *thread);

private:
    ExpiringThread *createThread();

    QVector<ExpiringThread *> m_threads;
};

#endif // THREADPOOL_HPP
