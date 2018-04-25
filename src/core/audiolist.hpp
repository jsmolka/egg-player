#ifndef AUDIOLIST_HPP
#define AUDIOLIST_HPP

#include <QList>

#include "audio.hpp"

/*
 * The AudioList class is just a QList<Audio *>
 * with some extra functions.
 */
class AudioList : public QList<Audio *>
{
public:
    void sortByTitle();
    void sortByArtist();
    void sortByAlbum();
    void sortByTrack();
};

#endif // AUDIOLIST_HPP
