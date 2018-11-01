#ifndef BASSSTREAM_HPP
#define BASSSTREAM_HPP

#include <bass/bass.h>

#include "core/audio.hpp"
#include "core/bass/basserror.hpp"

namespace bass
{
class Stream : private Error
{
public:
    explicit Stream();

    HSTREAM handle() const;
    HSYNC sync() const;

    bool isHandleValid() const;
    bool isSyncValid() const;

    bool isPlaying() const;
    bool isPaused() const;
    bool isStopped() const;
    bool isStalled() const;

    bool play() const;
    bool pause() const;

    bool create(Audio *audio);
    bool free();

    bool setPosition(int position) const;
    int position() const;

    bool setVolume(float volume) const;
    float volume() const;

    bool setDevice(DWORD device) const;
    DWORD device() const;

    bool setCallback(SYNCPROC *proc, void *user);
    bool removeCallback();

private:
    HSTREAM m_handle;
    HSYNC m_sync;
};
}

#endif // BASSSTREAM_HPP
