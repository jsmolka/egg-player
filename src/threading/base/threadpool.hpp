#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <QTimer>
#include <QVector>

#include "thread.hpp"
#include "threadedobject.hpp"

class ThreadPool : public QObject
{
    Q_OBJECT

public:
    explicit ThreadPool(QObject *parent = nullptr);

    static ThreadPool *instance();
    QVector<Thread *> threads() const;

    Thread *getSuitibleThread(const ThreadedObject &object);

public slots:
    void interruptThreads();

private slots:
    void onTimeout();

private:
    Thread *createThread();

    static constexpr int s_timeout = 60000;

    QVector<Thread *> m_threads;
    QTimer m_timer;
};

#endif // THREADPOOL_HPP
