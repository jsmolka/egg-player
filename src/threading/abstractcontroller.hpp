#ifndef ABSTRACTCONTROLLER_HPP
#define ABSTRACTCONTROLLER_HPP

#include <QThread>
#include <QObject>
#include <QVector>

#include "abstractworker.hpp"
#include "logger.hpp"

class AbstractController : public QObject
{
    Q_OBJECT

public:
    AbstractController(QObject *parent = nullptr);
    ~AbstractController();

    QVector<AbstractWorker *> workers() const;
    QVector<QThread *> threads() const;

    bool isRunning() const;
    bool isFinished() const;

    QThread * createWorkerThread(AbstractWorker *worker);
    void stopWorkerThreads();

public slots:
    virtual void start() = 0;

signals:
    void finished();

private slots:
    void workerFinished();
    void removeWorker(QObject *object);
    void removeThread(QObject *object);

private:    
    template<typename T>
    void removeObject(QVector<T> &vector, QObject *object);

    QVector<AbstractWorker *> m_workers;
    QVector<QThread *> m_threads;

    int m_finished;
    int m_total;
};

#endif // ABSTRACTCONTROLLER_HPP
