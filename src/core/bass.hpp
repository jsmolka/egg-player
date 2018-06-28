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

    BassStream stream();

    bool start();
    bool pause();
    bool stop();

    bool setVolume(float volume);
    float volume();

    bool setDevice(DWORD device);
    DWORD device();

    BASS_DEVICEINFO deviceInfo();

private:
    BassStream m_stream;

    bool init();
    bool free();
};

#endif // BASSWRAPPER_HPP
