#ifndef AUDIOUPDATER_HPP
#define AUDIOUPDATER_HPP

#include "core/audio.hpp"
#include "core/globals.hpp"
#include "threading/core/callable.hpp"

class AudioUpdater : public Callable
{
    Q_OBJECT

public:
    explicit AudioUpdater(QObject *parent = nullptr);

signals:
    void updated(Audio *audio);

public slots:
    void update(Audio *audio);
};

#endif // AUDIOUPDATER_HPP
