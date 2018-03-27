#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QList>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QPixmap>

#include "src/core/audio.hpp"
#include "src/core/audiolist.hpp"
#include "src/core/playlist.hpp"

class Player : public QMediaPlayer
{
    Q_OBJECT

    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex)
    Q_PROPERTY(bool loop READ isLoop WRITE setLoop)

public:
    Player(QObject *parent = 0);

    bool isShuffled() const;

    void setAudioList(const AudioList &audioList);

    void setCurrentIndex(int index);
    int currentIndex() const;

    void setLoop(bool loop);
    bool isLoop() const;

    Audio * currentAudio();

    int nextIndex();
    int backIndex();

    void shuffle();
    void unshuffle();

private:
    QList<QMediaContent> mediaContent(int start, int end);

    QMediaPlaylist *pm_playlist;
    Playlist m_playlist;
    bool m_shuffled;
};

#endif // PLAYER_HPP
