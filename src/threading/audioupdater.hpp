#ifndef AUDIOUPDATER_HPP
#define AUDIOUPDATER_HPP

#include "core/audio.hpp"
#include "threading/core/callable.hpp"

class AudioUpdater : public Callable
{
    Q_OBJECT

public:
    using Callable::Callable;

signals:
    void updated(Audio *audio);

public slots:
    void update(Audio *audio);

private:
    bool updateAudio(Audio *audio);
    bool loadCover(Audio *audio);
};

#endif // AUDIOUPDATER_HPP
