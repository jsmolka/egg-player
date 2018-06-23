#ifndef ABSTRACTTHREAD_HPP
#define ABSTRACTTHREAD_HPP

#include <QThread>

#include "logger.hpp"

class AbstractThread : public QThread
{
    Q_OBJECT

public:
    AbstractThread(QObject *parent = nullptr);
    ~AbstractThread();

    bool isAbort() const;

signals:
    void terminated();

public slots:
    void abort();

private slots:
    void onStarted();

private:
    bool m_abort;
};

#endif // ABSTRACTTHREAD_HPP
