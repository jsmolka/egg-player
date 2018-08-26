#ifndef THREADEDOBJECT_HPP
#define THREADEDOBJECT_HPP

#include <QObject>

class ThreadedObject : public QObject
{
public:
    explicit ThreadedObject(QObject *parent = nullptr);
};

#endif // THREADEDOBJECT_HPP
