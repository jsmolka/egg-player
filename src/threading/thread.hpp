#ifndef THREAD_HPP
#define THREAD_HPP

#include <QThread>

#include "core/macros.hpp"

class Thread : public QThread
{
    Q_OBJECT

public:
    explicit Thread(QObject *parent = nullptr);

    EGG_P_PROP(int, objects, setObjects, objects)
    EGG_P_PROP(int, maxObjects, setMaxObjects, maxObjects)

    void incrementObjects();
    void decrementObjects();

    bool isEmpty() const;
    bool isFull() const;

public slots:
    void interrupt();
    void waitToQuit();

signals:
    void interrupted();
    void emptied();
};

#endif // THREAD_HPP
