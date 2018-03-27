#ifndef AUDIOLIST_HPP
#define AUDIOLIST_HPP

#include <algorithm>

#include <QList>

#include "src/core/audio.hpp"

class AudioList : public QList<Audio>
{
public:
    void sortByTitle();
    void sortByArtist();
    void sortByAlbum();
    void sortByTrack();
};

#endif // AUDIOLIST_HPP
