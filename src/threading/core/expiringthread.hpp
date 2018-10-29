#ifndef EXPIRINGTHREAD_HPP
#define EXPIRINGTHREAD_HPP

#include <QTimer>

#include "threading/core/thread.hpp"

class ExpiringThread : public QObject
{
    Q_OBJECT

public:
    explicit ExpiringThread(QObject *parent = nullptr);

    Thread *thread();

signals:
    void expired(ExpiringThread *thread);

private slots:
    void onTimeout();
    void onEmptied();
    void onAppQuitting();

private:
    Thread *m_thread;
    QTimer m_timer;
    bool m_quitting;
};

#endif // EXPIRINGTHREAD_HPP
