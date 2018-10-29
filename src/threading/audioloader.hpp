#ifndef AUDIOLOADER_HPP
#define AUDIOLOADER_HPP

#include "core/audio.hpp"
#include "threading/core/callable.hpp"

class AudioLoader : public Callable
{
    Q_OBJECT

public:
    using Callable::Callable;

public slots:
    void load(const QString &file);

signals:
    void loaded(Audio *audio);

private:
    bool insertAudio(Audio *audio) const;
    bool updateAudio(Audio *audio) const;
    bool loadCover(Audio *audio) const;
};

#endif // AUDIOLOADER_HPP
