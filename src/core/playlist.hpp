#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP

#include <QObject>
#include <QVector>

#include "audio.hpp"

struct PlaylistItem
{
    PlaylistItem(int index = 0, Audio *audio = nullptr) :
        index(index), audio(audio) {}

    int index;
    Audio *audio;
};

class Playlist : public QObject
{
    Q_OBJECT

public:
    Playlist(QObject *parent = nullptr);
    ~Playlist();

    void setIndex(int index);
    int index() const;

    void setLoop(bool loop);
    bool isLoop() const;

    void setShuffle(bool shuffle);
    bool isShuffle() const;

    void changeIndex(int index);

    Audio * audioAt(int index);
    Audio * currentAudio();

    void next();
    void previous();

    void loadAudios(const Audios &audios);

signals:
    void indexChanged(int index);

private:
    bool validIndex(int index);
    int nextIndex();
    int previousIndex();

    int indexOf(const Audio *audio);
    void shuffle();
    void unshuffle();

    QVector<PlaylistItem> m_items;
    int m_index;
    bool m_loop;
    bool m_shuffle;
};

#endif // PLAYLIST_HPP
