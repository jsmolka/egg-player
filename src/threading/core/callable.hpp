#ifndef CALLABLE_HPP
#define CALLABLE_HPP

#include <QMetaObject>

#include "threading/core/threadedobject.hpp"

class Callable : public ThreadedObject
{
    Q_OBJECT

public:
    explicit Callable(QObject *parent = nullptr);
    ~Callable() override;

    Thread *thread();

    void moveToThread(Thread *thread) override;

protected:
    void invoke(QObject *object, const char *method, QGenericArgument arg = QGenericArgument(nullptr));

private:
    static constexpr int s_objectsPerThread{8};

    Thread *m_thread;
};

#endif // CALLABLE_HPP
