#include "abstractcontroller.hpp"

AbstractController::AbstractController(QObject *parent)
    : QObject(parent)
{

}

AbstractController::~AbstractController()
{

}

QThread * AbstractController::createWorkerThread(AbstractWorker *worker)
{
    QThread *thread = new QThread;
    m_worker << worker;

    worker->moveToThread(thread);
    connect(qApp, SIGNAL(aboutToQuit()), worker, SLOT(interrupt()));
    connect(thread, SIGNAL(started()), worker, SLOT(work()));
    connect(worker, SIGNAL (finished()), thread, SLOT (quit()));
    connect(worker, SIGNAL (finished()), worker, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    thread->start();

    return thread;
}
