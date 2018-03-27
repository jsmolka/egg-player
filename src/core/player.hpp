#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <time.h>

#include <QList>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QPixmap>
#include <QWidget>

#include "src/core/audio.hpp"
#include "src/core/audiolist.hpp"

class Player : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex)
    Q_PROPERTY(bool loop READ isLoop WRITE setLoop)
    Q_PROPERTY(bool shuffled READ isShuffled WRITE setShuffled)

public:
    Player(QWidget *parent = 0);

    void setCurrentIndex(int index);
    int currentIndex();

    void setLoop(bool loop);
    bool isLoop() const;

    void setShuffled(bool shuffle);
    bool isShuffled() const;

    int volume();
    int position();

    bool isPlaying() const;

    void setAudioList(AudioList audioList);

    Audio audioAt(int index);
    Audio currentAudio();

    int nextIndex();
    int backIndex();

    void shuffle();
    void unshuffle();

public slots:
    void setVolume(int volume);
    void setPosition(int position);

    void play();
    void pause();
    void next();
    void back();

signals:
    void changed();
    void stopped();

private slots:
    void autoPlay(int index);
    void audioChanged();

private:
    struct AudioPosition
    {
        AudioPosition(int i, Audio a)
        {
            index = i;
            audio = a;
        }

        int index;
        Audio audio;
    };

    void insertAudio(int index);

    QMediaPlayer *pm_player;
    QList<AudioPosition> m_playlist;
    int m_currentIndex;
    bool m_loop;
    bool m_shuffled;
    bool m_playing;

};

#endif // PLAYER_HPP
