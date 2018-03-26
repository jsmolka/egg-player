#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <time.h>

#include <QList>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QPixmap>

#include <src/core/audio.hpp>
#include <src/core/audiolist.hpp>

class Player : public QMediaPlayer
{
public:
    Player(QObject *parent = 0);

    void setAudioList(const AudioList &audioList);
    AudioList audioList() const;

    void setCurrentIndex(int index);
    int currentIndex() const;

    Audio * currentAudio();
    QString currentTitle();
    QString currentArtist();
    QPixmap currentCover();

    QString titleAt(int index);
    QString artistAt(int index);
    QPixmap coverAt(int index);

    void setLoop(bool loop);
    bool isLoop();

    int nextIndex();
    int backIndex();

    void refresh();
    void shuffle();

private:
    QMediaPlaylist *pm_playlist;
    AudioList m_audioList;
};

#endif // PLAYER_HPP
