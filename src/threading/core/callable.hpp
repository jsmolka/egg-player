#ifndef CALLABLE_HPP
#define CALLABLE_HPP

#include "threading/core/threadobject.hpp"

class Callable : public ThreadObject
{
    Q_OBJECT

public:
    explicit Callable(QObject *parent = nullptr);
    ~Callable() override;

    int objectsPerThread() const override;

    void moveToThread(Thread *thread) override;

private:
    Thread *m_thread;
};

#endif // CALLABLE_HPP
