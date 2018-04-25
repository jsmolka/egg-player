#ifndef AUDIOLIST_HPP
#define AUDIOLIST_HPP

#include <QList>

#include "audio.hpp"

class AudioList : public QList<Audio *>
{
public:
    void sortByTitle();
    void sortByArtist();
    void sortByAlbum();
    void sortByTrack();
};

#endif // AUDIOLIST_HPP
