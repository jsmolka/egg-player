#ifndef THREAD_HPP
#define THREAD_HPP

#include <QThread>
#include <QTimer>

class Thread : public QThread
{
    Q_OBJECT

public:
    explicit Thread(QObject *parent = nullptr);

    void setObjectCount(int count);
    int objectCount() const;

    void setMaxObjectCount(int count);
    int maxObjectCount() const;

    bool isEmpty() const;
    bool isFull() const;

public slots:
    void interrupt();
    void waitToQuit();

signals:
    void interrupted();

private slots:
    void onTimeout();

private:
    static constexpr int s_waitTimeout = 2500;
    static constexpr int s_threadTimeout = 30000;

    QTimer m_timeout;
    int m_objectCount;
    int m_maxObjectCount;
};

#endif // THREAD_HPP
