#ifndef BASS_STREAMWRAPPER_HPP
#define BASS_STREAMWRAPPER_HPP

#include <bass/bass.h>

#include "core/audio.hpp"
#include "core/bass/basserror.hpp"

namespace bass
{

class StreamWrapper : protected BassError
{
public:
    StreamWrapper();

    HSTREAM handle() const;

    bool isValid() const;
    bool isPlaying() const;

    bool setPosition(int position) const;
    int position() const;

    bool setVolume(float volume) const;
    float volume() const;

    bool play() const;
    bool pause() const;

    bool create(const Audio &audio);

private:
    bool free();

    HSTREAM m_handle;
};

}

#endif // BASS_STREAMWRAPPER_HPP
