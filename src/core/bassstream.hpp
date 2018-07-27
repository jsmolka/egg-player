#ifndef BASSSTREAM_HPP
#define BASSSTREAM_HPP

#include "bass/bass.h"

#include "audio.hpp"
#include "basserror.hpp"

class BassStream : public BassError
{
public:
    BassStream();
    ~BassStream();

    HSTREAM handle() const;

    bool isValid() const;

    bool isPlaying() const;
    bool isPaused() const;
    bool isStopped() const;
    bool isStalled() const;

    bool play();
    bool pause();

    bool create(Audio *audio);
    bool free();

    bool setPosition(int position);
    int position();

    bool setVolume(float volume);
    float volume();

    bool setDevice(DWORD device);
    DWORD device();

    bool setCallback(SYNCPROC *proc, void *user);
    bool removeCallback();

private:
    HSTREAM m_handle;
    HSYNC m_sync;
};

#endif // BASSSTREAM_HPP
