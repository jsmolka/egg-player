#include "abstractcontroller.hpp"

#include "logger.hpp"

AbstractController::AbstractController(QObject *parent)
    : QObject(parent)
    , m_workers()
    , m_threads()
    , m_finished(0)
    , m_total(0)
{

}

AbstractController::~AbstractController()
{

}

QVector<AbstractWorker *> AbstractController::workers() const
{
    return m_workers;
}

QVector<QThread *> AbstractController::threads() const
{
    return m_threads;
}

bool AbstractController::isRunning() const
{
    for (const QThread *thread : m_threads)
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
        if (!thread->wait(m_timeout))
        {
            LOG("Could not exit thread within %1 ms", m_timeout);
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

void AbstractController::removeWorker(const QObject *object)
{
    removeObject<AbstractWorker *>(m_workers, object);
}

void AbstractController::removeThread(const QObject *object)
{
    removeObject<QThread *>(m_threads, object);
}

template <typename T>
void AbstractController::removeObject(QVector<T> &vector, const QObject *object)
{
    for (auto iter = vector.begin(); iter != vector.end(); ++iter)
    {
        if (*iter == object)
        {
            vector.erase(iter);
            break;
        }
    }
}
