#include "controller.hpp"

Controller::Controller(QObject *parent)
    : QObject(parent)
    , m_activeWorker(0)
{

}

void Controller::runWorker(Runnable *worker)
{
    m_activeWorker++;
    connect(worker, &Runnable::finished, this, &Controller::onWorkerFinished);
    worker->run();
}

void Controller::onWorkerFinished()
{
    if (--m_activeWorker == 0)
        emit finished();
}
