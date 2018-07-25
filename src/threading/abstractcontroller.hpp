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

    QThread * createWorkerThread(AbstractWorker *worker);

    bool isRunning() const;
    bool isFinished() const;

    void interrupt();
    void quit();
    void wait();

    virtual void start() = 0;

private slots:
    void removeWorker(QObject *object);
    void removeThread(QObject *object);

private:    
    QVector<AbstractWorker *> m_workers;
    QVector<QThread *> m_threads;
};

#endif // ABSTRACTCONTROLLER_HPP
