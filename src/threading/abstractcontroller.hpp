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
    explicit AbstractController(QObject *parent = nullptr);

    QVector<AbstractWorker *> workers() const;
    QVector<QThread *> threads() const;

    bool isRunning() const;
    bool isFinished() const;

    QThread *createWorkerThread(AbstractWorker *worker);
    void stopWorkerThreads();

public slots:
    virtual void start() = 0;

signals:
    void finished();

protected:
    template <typename T>
    static inline QVector<QVector<T>> chunk(const QVector<T> &vector, int n);

private slots:
    void workerFinished();
    void removeWorker(QObject *object);
    void removeThread(QObject *object);

private:    
    template <typename T>
    static inline void removeObject(QVector<T> &vector, QObject *object);

    static constexpr int s_timeout = 2500;

    QVector<AbstractWorker *> m_workers;
    QVector<QThread *> m_threads;

    int m_finished;
    int m_total;
};

template <typename T>
inline QVector<QVector<T>> AbstractController::chunk(const QVector<T> &vector, int n)
{
    n = qBound(1, n, vector.size());
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

template <typename T>
inline void AbstractController::removeObject(QVector<T> &vector, QObject *object)
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

#endif // ABSTRACTCONTROLLER_HPP
