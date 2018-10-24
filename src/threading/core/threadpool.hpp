#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <QVector>

#include "threading/core/expiringthread.hpp"
#include "threading/core/threadedobject.hpp"

class ThreadPool : public QObject
{
    Q_OBJECT

public:
    explicit ThreadPool(QObject *parent = nullptr);

    static ThreadPool *instance();

    Thread *getSuitibleThread(const ThreadedObject &object);

public slots:
    void interruptThreads();

private slots:
    void onThreadExpired(ExpiringThread *thread);

private:
    ExpiringThread *createThread();

    QVector<ExpiringThread *> m_threads;
};

#endif // THREADPOOL_HPP
