#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <time.h>

#include <QList>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QPixmap>

#include "src/core/audio.hpp"
#include "src/core/audiolist.hpp"

class Player : public QMediaPlayer
{
    Q_OBJECT

    Q_PROPERTY(AudioList audioList READ audioList WRITE setAudioList)
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex)
    Q_PROPERTY(bool loop READ isLoop WRITE setLoop)

public:
    Player(QObject *parent = 0);

    void setAudioList(const AudioList &audioList);
    AudioList audioList() const;

    void setCurrentIndex(int index);
    int currentIndex() const;

    void setLoop(bool loop);
    bool isLoop() const;

    Audio * currentAudio();

    int nextIndex();
    int backIndex();

    void refresh();
    void shuffle();

private:
    QMediaPlaylist *pm_playlist;
    AudioList m_audioList;
};

#endif // PLAYER_HPP
