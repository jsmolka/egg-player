#ifndef RUNNABLE_HPP
#define RUNNABLE_HPP

#include "threading/core/threadobject.hpp"

class Runnable : public ThreadObject
{
    Q_OBJECT

public:
    explicit Runnable(QObject *parent = nullptr);
    ~Runnable() override;

    Thread *thread();

    int objectsPerThread() const override;
    void moveToThread(Thread *thread) override;

public slots:
    void run();

signals:
    void finished();

private slots:
    virtual void work() = 0;

private:
    Thread *m_thread;
};

#endif // RUNNABLE_HPP
