#ifndef THREADEDOBJECT_HPP
#define THREADEDOBJECT_HPP

#include <QObject>

#include "thread.hpp"

class ThreadedObject : public QObject
{
    Q_OBJECT

public:
    explicit ThreadedObject(QObject *parent = nullptr);

    void setObjectsPerThread(int objects);
    int objectsPerThread() const;

    bool isInterrupted() const;

    virtual void moveToThread(Thread *thread) = 0;

public slots:
    void interrupt();

    void moveToMainThread();

private:
    int m_objectsPerThread;
    bool m_interrupted;
};

#endif // THREADEDOBJECT_HPP
