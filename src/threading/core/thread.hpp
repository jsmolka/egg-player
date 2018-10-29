#ifndef THREAD_HPP
#define THREAD_HPP

#include <QThread>

#include "core/globals.hpp"

class Thread : public QThread
{
    Q_OBJECT

public:
    explicit Thread(QObject *parent = nullptr);

    EGG_PPROP(int, objects, setObjects, objects)
    EGG_PPROP(int, maxObjects, setMaxObjects, maxObjects)

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
