#include "controller.hpp"

Controller::Controller(QObject *parent)
    : QObject(parent)
    , m_running(0)
{

}

int Controller::runningWorker() const
{
    return m_running;
}

void Controller::runWorker(Runnable *runnable)
{
    connect(runnable, &Runnable::finished, this, &Controller::onWorkerFinished);
    ++m_running;
    runnable->run();
}

void Controller::onWorkerFinished()
{
    if (--m_running == 0)
        emit finished();
}
