#ifndef CACHE_HPP
#define CACHE_HPP

#include <QPixmap>
#include <QString>

#include "core/audio.hpp"
#include "core/globals.hpp"

class Cache
{
public:
    static Audio *loadAudio(const QString &file);
    static bool insertAudio(Audio *audio);
    static bool updateAudio(Audio *audio);
    static bool updateAudioCover(Audio *audio, const QPixmap &cover);

private:
    static bool updateAudioCoverId(Audio *audio, int coverId);
};

#endif // CACHE_HPP
