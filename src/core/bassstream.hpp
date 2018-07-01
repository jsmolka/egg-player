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

    bool play();
    bool pause();

    bool create(Audio *audio, bool prescan = false);
    bool free();

    bool setPosition(int position);
    int position();

    bool setVolume(float volume);
    float volume();

    bool setDevice(DWORD device);
    DWORD device();

private:
    HSTREAM m_handle;
};

#endif // BASSSTREAM_HPP
