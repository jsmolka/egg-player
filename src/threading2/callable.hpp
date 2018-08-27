#ifndef CALLABLE_HPP
#define CALLABLE_HPP

#include "threadedobject.hpp"

class Callable : public ThreadedObject
{
public:
    explicit Callable(QObject *parent = nullptr);

    void moveToThread(Thread *thread);
};

#endif // CALLABLE_HPP
