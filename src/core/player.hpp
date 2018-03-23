#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <time.h>

#include <QList>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <src/core/audio.hpp>
#include <src/core/audiolist.hpp>

class Player : public QMediaPlayer
{
public:
    Player(QObject *parent = 0);

    void setAudioList(AudioList audioList);
    AudioList audioList() const;

    QMediaPlaylist * playlist() const;

    void setIndex(quint32 index);
    quint32 index() const;
    Audio audio() const;

    void setPlaybackMode(QMediaPlaylist::PlaybackMode mode);

    bool refresh();
    void shuffle();

private:
    QMediaPlaylist *pm_playlist;
    AudioList m_audioList;
};

#endif // PLAYER_HPP
