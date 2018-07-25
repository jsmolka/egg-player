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

    worker->moveToThread(thread);
    connect(thread, SIGNAL(started()), worker, SLOT(work()));
    connect(worker, SIGNAL(finished()), thread, SLOT (quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT (deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT (deleteLater()));
    connect(thread, SIGNAL(destroyed(QObject *)), this, SLOT(removeThread(QObject *)));
    connect(worker, SIGNAL(destroyed(QObject *)), this, SLOT(removeWorker(QObject *)));
    thread->start();

    m_workers << worker;
    m_threads << thread;

    return thread;
}

bool AbstractController::isRunning() const
{
    for (QThread *thread : m_threads)
    {
        if (thread->isRunning())
            return true;
    }
    return false;
}

bool AbstractController::isFinished() const
{
    return !isRunning();
}

void AbstractController::interrupt()
{
    for (AbstractWorker *worker : m_workers)
        worker->interrupt();
}

void AbstractController::quit()
{
    for (QThread *thread : m_threads)
        thread->quit();
}

void AbstractController::wait()
{
    for (QThread *thread : m_threads)
    {
        if (!thread->wait(2500))
        {
            log("AbstractController: Could not exit thread within 2.5 seconds");
            thread->terminate();
        }
    }
}

void AbstractController::removeWorker(QObject *object)
{
    for (int i = 0; i < m_workers.size(); ++i)
    {
        if (m_workers[i] == object)
        {
            m_workers.remove(i);
            break;
        }
    }
}

void AbstractController::removeThread(QObject *object)
{
    for (int i = 0; i < m_threads.size(); ++i)
    {
        if (m_threads[i] == object)
        {
            m_threads.remove(i);
            break;
        }
    }
}
