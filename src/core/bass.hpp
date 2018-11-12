#ifndef BASS_HPP
#define BASS_HPP

#include "core/bass/error.hpp"
#include "core/bass/streamwrapper.hpp"
#include "core/bass/syncwrapper.hpp"

class Bass : private bass::Error
{
public:
    Bass();
    ~Bass();

    const bass::StreamWrapper &stream() const;
    const bass::SyncWrapper &sync() const;

    bass::StreamWrapper &stream();
    bass::SyncWrapper &sync();

private:
    static bool isValidVersion();
    static bool setConfig();
    static bool init();
    static bool free();

    bass::StreamWrapper m_stream;
    bass::SyncWrapper m_sync;
};

#endif // BASS_HPP
