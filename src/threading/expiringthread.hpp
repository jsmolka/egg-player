#ifndef EXPIRINGTHREAD_HPP
#define EXPIRINGTHREAD_HPP

#include <QTimer>

#include "threading/thread.hpp"

class ExpiringThread : public QObject
{
    Q_OBJECT

public:
    explicit ExpiringThread(QObject *parent = nullptr);

    Thread *thread();

signals:
    void expired(ExpiringThread *thread);

private slots:
    void onEmptied();
    void onTimeout();
    void onQuitting();

private:
    Thread *m_thread;
    QTimer m_timer;
    bool m_quitting;
};

#endif // EXPIRINGTHREAD_HPP
