#ifndef ABSTRACTWORKER_HPP
#define ABSTRACTWORKER_HPP

#include <QApplication>
#include <QObject>

class AbstractWorker : public QObject
{
    Q_OBJECT

public:
    AbstractWorker(QObject *parent = nullptr);
    ~AbstractWorker();

    bool isInterrupt() const;

public slots:
    void interrupt();

    virtual void work() = 0;

signals:
    void finished();

private:
    bool m_interrupt;
};

#endif // ABSTRACTWORKER_HPP
