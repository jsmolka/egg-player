#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP

#include "src/core/audio.hpp"
#include "src/core/audiolist.hpp"
#include "src/utils/randutil.hpp"

class Playlist
{
public:
    struct Item
    {
        Item(int i, Audio *a) {
            index = i;
            audio = a;
        }

        Audio *audio;
        int index;
    };

    Playlist();
    Playlist(const AudioList &audioList);

    bool isShuffled() const;
    int size() const;

    void setAudioList(const AudioList &audioList);

    QList<Playlist::Item> * itemList();

    void sort();
    void shuffle(int index);

    Audio * audioAt(int index);

private:
    QList<Playlist::Item> m_itemList;
    bool m_shuffled;
};

#endif // PLAYLIST_HPP
