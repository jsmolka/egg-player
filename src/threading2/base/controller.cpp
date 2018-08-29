#include "controller.hpp"

Controller::Controller(QObject *parent)
    : QObject(parent)
    , m_running(0)
{

}

void Controller::setRunning(int running)
{
    m_running = running;
}

int Controller::running() const
{
    return m_running;
}

void Controller::onWorkerFinished()
{
    if (--m_running == 0)
        emit finished();
}
