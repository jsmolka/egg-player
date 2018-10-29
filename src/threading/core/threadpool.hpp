#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <QVector>

#include "threading/core/expiringthread.hpp"
#include "threading/core/threadobject.hpp"

#define egg_pool (ThreadPool::instance())

class ThreadPool : public QObject
{
    Q_OBJECT

public:
    explicit ThreadPool(QObject *parent = nullptr);
    explicit ThreadPool(const ThreadPool &) = delete;

    static ThreadPool &instance();

    Thread *getSuitibleThread(ThreadObject *object);

    void operator=(const ThreadPool &) = delete;

public slots:
    void interruptThreads();

private slots:
    void onThreadExpired(ExpiringThread *thread);

private:
    ExpiringThread *createThread();

    QVector<ExpiringThread *> m_threads;
};

#endif // THREADPOOL_HPP
