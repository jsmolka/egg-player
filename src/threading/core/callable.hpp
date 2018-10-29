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

protected:
    void invoke(QObject *object, const char *method, QGenericArgument arg = QGenericArgument(nullptr));

private:
    Thread *m_thread;
};

#endif // CALLABLE_HPP
