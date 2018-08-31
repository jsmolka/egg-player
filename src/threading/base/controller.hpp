#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QObject>
#include <QVector>

#include "runnable.hpp"

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(QObject *parent = nullptr);
    virtual ~Controller() = default;

    int running() const;

    void runWorker(Runnable *runnable);

public slots:
    virtual void start() = 0;

signals:
    void finished();

protected:
    template <typename T>
    static inline QVector<QVector<T>> chunk(const QVector<T> &vector, int n);

private:
    void onWorkerFinished();

private:
    int m_running;
};

template <typename T>
inline QVector<QVector<T>> Controller::chunk(const QVector<T> &vector, int n)
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

#endif // CONTROLLER_HPP
