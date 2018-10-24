#ifndef BASS_HPP
#define BASS_HPP

#include <functional>

#include <QAtomicInt>

#include <bass/bass.h>

#include "core/globals.hpp"
#include "core/bass/basserror.hpp"
#include "core/bass/bassstream.hpp"

class Bass : public BassError
{
public:
    Bass();
    ~Bass();

    static bool start();
    static bool pause();
    static bool stop();

    static bool setVolume(float volume);
    static float volume();

    static bool setDevice(DWORD device);
    static DWORD device();

    static BASS_DEVICEINFO deviceInfo();

    BassStream &stream();

private:
    static bool setConfig();
    static bool isValidVersion();
    static bool init();
    static bool free();

    static bool call(const std::function<BOOL()> &func);

    static QAtomicInt s_refs;

    BassStream m_stream;
};

#endif // BASS_HPP
