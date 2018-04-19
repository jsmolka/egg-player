#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QObject>

#include <bass/bass.h>

#include "audio.hpp"
#include "audiolist.hpp"
#include "timer.hpp"

class Player : public QObject
{
    Q_OBJECT

public:
    Player(QObject *parent = nullptr);
    ~Player();

    enum State {Playing, Paused};

    void setIndex(int index);
    int index() const;

    bool isLoop() const;
    bool isShuffled() const;

    int volume() const;
    int position() const;

    bool isPlaying() const;

    void setPlaylist(const AudioList &playlist);

    Audio * audioAt(int index) const;
    Audio * currentAudio() const;

public slots:
    void setVolume(int volume);
    void setPosition(int position);

    void setLoop(bool loop);
    void setShuffled(bool shuffled);

    void play();
    void pause();
    void next();
    void back();

signals:
    void audioChanged(Audio *audio);
    void stateChanged(Player::State state);
    void positionChanged(int position);
    void volumeChanged(int volume);

private slots:
    void onTimeout(qint64 total);

private:
    struct AudioPosition
    {
        AudioPosition(int i, Audio *a)
        {
            index = i;
            audio = a;
        }

        int index;
        Audio *audio;
    };

    int nextIndex();
    int backIndex();

    void shuffle();
    void unshuffle();

    void freeStream();
    void setAudio(int index);

    QList<AudioPosition> m_playlist;
    Timer *pm_timer;
    HSTREAM m_stream;
    int m_index;
    int m_volume;
    bool m_loop;
    bool m_shuffled;
    bool m_playing;
};

#endif // PLAYER_HPP
