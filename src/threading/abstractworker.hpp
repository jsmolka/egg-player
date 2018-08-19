#ifndef ABSTRACTWORKER_HPP
#define ABSTRACTWORKER_HPP

#include <QObject>

class AbstractWorker : public QObject
{
    Q_OBJECT

public:
    explicit AbstractWorker(QObject *parent = nullptr);
    ~AbstractWorker();

    bool isInterrupted() const;

public slots:
    void interrupt();

    virtual void work() = 0;

signals:
    void finished();

private:
    bool m_interrupted;
};

#endif // ABSTRACTWORKER_HPP
