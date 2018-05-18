#ifndef ABSTRACTTHREAD_HPP
#define ABSTRACTTHREAD_HPP

#include <QApplication>
#include <QThread>

class AbstractThread : public QThread
{
    Q_OBJECT

public:
    AbstractThread(QObject *parent = nullptr);
    ~AbstractThread();

    bool isAbort() const;

public slots:
    void abort();

private:
    bool m_abort;
};

#endif // ABSTRACTTHREAD_HPP
