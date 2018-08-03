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

protected:
    template <typename T>
    QVector<QVector<T>> chunk(const QVector<T> &vector, int n)
    {
        n = qMin(qMax(1, n), vector.size());
        int quo = vector.size() / n;
        int rem = vector.size() % n;

        QVector<QVector<T>> result;
        for (int i = 0; i < n; ++i)
        {
            int l = i * quo + qMin(i, rem);
            int r = (i + 1) * quo + qMin(i + 1, rem);
            result << vector.mid(l, r - l);
        }
        return result;
    }

private slots:
    void workerFinished();
    void removeWorker(const QObject *object);
    void removeThread(const QObject *object);

private:    
    template <typename T>
    void removeObject(QVector<T> &vector, const QObject *object);

    QVector<AbstractWorker *> m_workers;
    QVector<QThread *> m_threads;

    int m_finished;
    int m_total;
};

#endif // ABSTRACTCONTROLLER_HPP
