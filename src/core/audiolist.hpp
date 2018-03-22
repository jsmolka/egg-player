#ifndef AUDIOLIST_HPP
#define AUDIOLIST_HPP

#include <algorithm>

#include <QList>

#include "src/core/audio.hpp"

class AudioList : public QList<Audio>
{
public:
    void sortByTitle(bool reverse = false);
    void sortByArtist(bool reverse = false);
    void sortByAlbum(bool reverse = false);
    void sortByTrack(bool reverse = false);
};

#endif // AUDIOLIST_HPP
