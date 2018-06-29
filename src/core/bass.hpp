#ifndef BASSWRAPPER_HPP
#define BASSWRAPPER_HPP

#include "bass/bass.h"

#include "logger.hpp"

#include "basserror.hpp"
#include "bassstream.hpp"

class Bass : public BassError
{
public:
    Bass();
    ~Bass();

    BassStream * stream();

    bool start();
    bool pause();
    bool stop();

    bool setVolume(float volume);
    float volume();

    bool setDevice(DWORD device);
    DWORD device();

    BASS_INFO info();
    BASS_DEVICEINFO deviceInfo();

private:
    bool init();
    bool free();

    BassStream m_stream;
};

#endif // BASSWRAPPER_HPP
