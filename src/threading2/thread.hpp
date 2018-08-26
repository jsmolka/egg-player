#ifndef THREAD_HPP
#define THREAD_HPP

#include <QThread>

class Thread : public QThread
{
public:
    explicit Thread(QObject *parent = nullptr);

    void setShared(bool shared);
    bool isShared() const;

private:
    bool m_shared;
};

#endif // THREAD_HPP
