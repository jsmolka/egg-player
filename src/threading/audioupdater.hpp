#ifndef AUDIOUPDATER_HPP
#define AUDIOUPDATER_HPP

#include "core/audio.hpp"
#include "threading/callable.hpp"

class AudioUpdater : public Callable
{
    Q_OBJECT

public:
    using Callable::Callable;

public slots:
    void update(Audio audio);

signals:
    void updated(Audio audio);

private:
    bool updateAudio(Audio &audio) const;
    bool loadCover(Audio &audio) const;
};

#endif // AUDIOUPDATER_HPP
