#ifndef BASSWRAPPER_HPP
#define BASSWRAPPER_HPP

#include "bass/bass.h"

#include "basserror.hpp"
#include "bassstream.hpp"
#include "logger.hpp"

class Bass : public BassError
{
public:
    Bass();
    ~Bass();

    BassStream * stream();

    bool isInit() const;

    bool start();
    bool pause();
    bool stop();

    bool setVolume(float volume);
    float volume();

    bool setDevice(DWORD device);
    DWORD device();

    BASS_DEVICEINFO deviceInfo();

private:
    bool setConfig();
    bool isValidVersion();
    bool init();
    bool free();

    bool call(BOOL(*func)());

    BassStream m_stream;

    static bool _init;
    static int _instances;
};

#endif // BASSWRAPPER_HPP
