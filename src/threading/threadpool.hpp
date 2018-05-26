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
    bool isRunning() const;

    int current(bool global = false) const;
    int ideal() const;
    int advised() const;

    int add(AbstractThread *thread);
    void start(int index = -1);

signals:
    void finished();

private slots:
    void onThreadFinished();

private:    
    void startAll();
    void startAt(int index);

    QVector<AbstractThread *> m_threads;
    int m_finished;

    static int _count;
};

#endif // THREADPOOL_HPP
