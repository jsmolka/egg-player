#include "abstractcontroller.hpp"

AbstractController::AbstractController(QObject *parent)
    : QObject(parent)
    , m_finished(0)
    , m_total(0)
{

}

AbstractController::~AbstractController()
{

}

QThread * AbstractController::createWorkerThread(AbstractWorker *worker)
{
    QThread *thread = new QThread;

    worker->moveToThread(thread);
    connect(thread, &QThread::started, worker, &AbstractWorker::work);
    connect(worker, &AbstractWorker::finished, thread, &QThread::quit);
    connect(worker, &AbstractWorker::finished, worker, &AbstractWorker::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    connect(thread, &QThread::destroyed, this, &AbstractController::removeThread);
    connect(worker, &AbstractWorker::destroyed, this, &AbstractController::removeWorker);
    connect(worker, &AbstractWorker::finished, this, &AbstractController::workerFinished);
    thread->start();

    m_workers << worker;
    m_threads << thread;
    ++m_total;

    return thread;
}

void AbstractController::stopWorkerThreads()
{
    for (AbstractWorker *worker : m_workers)
        worker->interrupt();

    for (QThread *thread : m_threads)
    {
        thread->quit();
        if (!thread->wait(2500))
        {
            log("AbstractController: Could not exit thread within 2.5 seconds");
            thread->terminate();
            thread->wait();
        }
    }
}

void AbstractController::workerFinished()
{
    if (++m_finished == m_total)
        emit finished();
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
