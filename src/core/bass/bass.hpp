#ifndef BASS_HPP
#define BASS_HPP

#include <bass/bass.h>

#include "core/globals.hpp"
#include "core/bass/basserror.hpp"
#include "core/bass/bassstream.hpp"

#define egg_bass (Bass::instance())

class Bass : private BassError
{
public:
    explicit Bass();
    explicit Bass(const Bass &) = delete;
    ~Bass();

    static Bass &instance();

    BassStream &stream();

    static bool start();
    static bool pause();
    static bool stop();

    static bool setVolume(float volume);
    static float volume();

    static bool setDevice(DWORD device);
    static DWORD device();

    static BASS_DEVICEINFO deviceInfo();

    void operator=(const Bass &) = delete;

private:
    static bool isValidVersion();
    static bool setConfig();
    static bool init();
    static bool free();

    BassStream m_stream;
};

#endif // BASS_HPP
