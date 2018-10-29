#ifndef THREADOBJECT_HPP
#define THREADOBJECT_HPP

#include <QObject>

#include "threading/core/thread.hpp"

class ThreadObject : public QObject
{
    Q_OBJECT

public:
    explicit ThreadObject(QObject *parent = nullptr);

    bool isInterrupted() const;

    virtual int objectsPerThread() const = 0;
    virtual void moveToThread(Thread *thread) = 0;

public slots:
    void interrupt();
    void moveToMainThread();

private:
    bool m_interrupted;
};

#endif // THREADOBJECT_HPP
