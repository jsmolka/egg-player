#include "testcallable.hpp"

#include <QDebug>

TestCallable::TestCallable(QObject *parent)
    : Callable(parent)
{

}

void TestCallable::doStuff()
{
    invoke(this, "doStuff_");
}

void TestCallable::doStuff_()
{
    while (true)
    {
        qDebug() << QThread::currentThread();
        QThread::msleep(100);
        if (isInterrupted())
            break;
    }
}
