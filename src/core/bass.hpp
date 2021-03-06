#ifndef BASS_HPP
#define BASS_HPP

#include "core/bass/streamwrapper.hpp"
#include "core/bass/syncwrapper.hpp"

class Bass : public bass::StreamWrapper
{
public:
    Bass();
    ~Bass();

    const bass::SyncWrapper &sync() const;

    bass::SyncWrapper &sync();

    bool applySync();

private:
    static bool init();
    static bool free();
    static bool isValidVersion();
    static bool setConfig();

    bass::SyncWrapper m_sync;
};

#endif // BASS_HPP
