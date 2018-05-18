#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <QObject>
#include <QThread>
#include <QVector>

#include "abstractthread.hpp"
#include "logger.hpp"

class ThreadPool : public QObject
{
    Q_OBJECT

public:
    ThreadPool(QObject *parent = nullptr);
    ~ThreadPool();

    bool isFinished() const;

    int idealCount() const;
    int currentCount() const;
    int advisedCount() const;

    void add(AbstractThread *thread);
    void start();

signals:
    void finished();

private slots:
    void onThreadFinished();

private:
    QVector<AbstractThread *> m_threads;
    int m_finished;

    static int _count;
};

#endif // THREADPOOL_HPP
