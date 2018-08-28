#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <QVector>

#include "thread.hpp"
#include "threadedobject.hpp"

class ThreadPool : public QObject
{
    Q_OBJECT

public:
    explicit ThreadPool(QObject *parent = nullptr);

    static ThreadPool *instance();

    Thread *getSuitibleThread(const ThreadedObject &object);

public slots:
    void interruptThreads();

private:
    Thread *createThread();

    QVector<Thread *> m_threads;
};

#endif // THREADPOOL_HPP
