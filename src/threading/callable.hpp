#ifndef CALLABLE_HPP
#define CALLABLE_HPP

#include "threading/threadobject.hpp"

class Callable : public ThreadObject
{
    Q_OBJECT

public:
    Callable();
    ~Callable() override;

    int objectsPerThread() const override;

private:
    void moveToThread(Thread *thread) override;

    Thread *m_thread;
};

#endif // CALLABLE_HPP
