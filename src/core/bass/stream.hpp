#ifndef BASS_STREAM_HPP
#define BASS_STREAM_HPP

#include <bass/bass.h>

#include "core/audio.hpp"
#include "core/bass/error.hpp"

namespace bass
{

class Stream : private Error
{
public:
    Stream();

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

#endif // BASS_STREAM_HPP
