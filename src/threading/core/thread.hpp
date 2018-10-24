#ifndef THREAD_HPP
#define THREAD_HPP

#include <QThread>

#include "core/globals.hpp"

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
    void emptied();

private:
    static constexpr int s_timeout{2500};

    int m_objectCount;
    int m_maxObjectCount;
};

#endif // THREAD_HPP
