#ifndef ABSTRACTCONTROLLER_HPP
#define ABSTRACTCONTROLLER_HPP

#include <QObject>
#include <QThread>
#include <QVector>

#include "abstractworker.hpp"

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
    static QVector<QVector<T>> chunk(const QVector<T> &vector, int n)
    {
        n = qMin(qMax(1, n), vector.size());
        const int quo = vector.size() / n;
        const int rem = vector.size() % n;

        QVector<QVector<T>> result;
        for (int i = 0; i < n; ++i)
        {
            const int l = i * quo + qMin(i, rem);
            const int r = (i + 1) * quo + qMin(i + 1, rem);
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
    static void removeObject(QVector<T> &vector, const QObject *object);

    static constexpr int m_timeout = 2500;

    QVector<AbstractWorker *> m_workers;
    QVector<QThread *> m_threads;

    int m_finished;
    int m_total;
};

#endif // ABSTRACTCONTROLLER_HPP
