#ifndef THREADOBJECT_HPP
#define THREADOBJECT_HPP

#include <QObject>

#include "threading/core/thread.hpp"

class ThreadObject : public QObject
{
    Q_OBJECT

public:
    ThreadObject();

    bool isInterrupted() const;

    void moveToThread(QThread *) = delete;

    virtual int objectsPerThread() const = 0;

public slots:
    void interrupt();
    void moveToMainThread();

private:
    virtual void moveToThread(Thread *thread) = 0;

    bool m_interrupted;
};

#endif // THREADOBJECT_HPP
