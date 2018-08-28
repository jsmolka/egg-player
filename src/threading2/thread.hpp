#ifndef THREAD_HPP
#define THREAD_HPP

#include <QThread>

class Thread : public QThread
{
    Q_OBJECT

public:
    explicit Thread(QObject *parent = nullptr);

    void setShared(bool shared);
    bool isShared() const;

    void setObjectCount(int count);
    int objectCount() const;

public slots:
    void interrupt();
    void waitToQuit();

signals:
    void interrupted();

private:
    static constexpr int s_timeout = 2500;

    bool m_shared;
    int m_objectCount;
};

#endif // THREAD_HPP
