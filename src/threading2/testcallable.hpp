#ifndef TESTCALLABLE_HPP
#define TESTCALLABLE_HPP

#include "callable.hpp"

class TestCallable : public Callable
{
    Q_OBJECT

public:
    explicit TestCallable(QObject *parent = nullptr);

    void doStuff();

private slots:
    void doStuff_();
};

#endif // TESTCALLABLE_HPP
