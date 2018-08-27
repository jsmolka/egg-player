#ifndef THREADEDOBJECT_HPP
#define THREADEDOBJECT_HPP

#include <QObject>

#include "thread.hpp"

class ThreadedObject : public QObject
{
public:
    explicit ThreadedObject(QObject *parent = nullptr);

    void setObjectsPerThread(int objects);
    int objectsPerThread() const;

    virtual void moveToThread(Thread *thread) = 0;

public slots:
    void moveToMainThread();

private:
    int m_objectsPerThread;
};

#endif // THREADEDOBJECT_HPP
