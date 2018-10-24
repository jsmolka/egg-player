#ifndef RUNNABLE_HPP
#define RUNNABLE_HPP

#include "threading/core/threadedobject.hpp"

class Runnable : public ThreadedObject
{
    Q_OBJECT

public:
    explicit Runnable(QObject *parent = nullptr);
    ~Runnable() override;

    Thread *thread();

    void moveToThread(Thread *thread) override;

public slots:
    void run();

signals:
    void finished();

private slots:
    virtual void work() = 0;

private:
    static constexpr int s_objectsPerThread{1};

    Thread *m_thread;
};

#endif // RUNNABLE_HPP
