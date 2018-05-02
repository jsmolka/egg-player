#ifndef AUDIOLIST_HPP
#define AUDIOLIST_HPP

#include <QVector>

#include "audio.hpp"

class Audios : public QVector<Audio *>
{
public:
    void sortByTitle();
    void sortByArtist();
    void sortByAlbum();
    void sortByTrack();
};

#endif // AUDIOLIST_HPP
