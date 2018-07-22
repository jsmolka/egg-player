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

    bool isInterrupt() const;

signals:
    void terminated();

public slots:
    void interrupt();

private slots:
    void onStarted();

private:
    bool m_interrupt;
};

#endif // ABSTRACTTHREAD_HPP
