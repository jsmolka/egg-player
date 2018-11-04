#ifndef BASS_HPP
#define BASS_HPP

#include <bass/bass.h>

#include "core/singleton.hpp"
#include "core/bass/basserror.hpp"
#include "core/bass/bassstream.hpp"

#define egg_bass (Bass::instance())

class Bass : public Singleton<Bass>, private bass::Error
{
public:
    Bass();
    ~Bass();

    const bass::Stream &stream() const;

    bass::Stream &stream();

    static bool start();
    static bool pause();
    static bool stop();

    static bool setVolume(float volume);
    static float volume();

    static bool setDevice(DWORD device);
    static DWORD device();

    static BASS_DEVICEINFO deviceInfo();

private:
    static bool isValidVersion();
    static bool setConfig();
    static bool init();
    static bool free();

    bass::Stream m_stream;
};

#endif // BASS_HPP
