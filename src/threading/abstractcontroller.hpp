#ifndef ABSTRACTCONTROLLER_HPP
#define ABSTRACTCONTROLLER_HPP

#include <QThread>
#include <QObject>
#include <QVector>

#include "abstractworker.hpp"

class AbstractController : public QObject
{
    Q_OBJECT

public:
    AbstractController(QObject *parent = nullptr);
    ~AbstractController();

    QThread * createWorkerThread(AbstractWorker *worker);

public slots:
    virtual void start() = 0;

private:
    QVector<AbstractWorker *> m_worker;
};

#endif // ABSTRACTCONTROLLER_HPP
