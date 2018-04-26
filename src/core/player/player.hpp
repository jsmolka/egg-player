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
    bool isShuffle() const;
    bool isPlaying() const;

    int volume() const;
    int position() const;

    void loadPlaylist(const AudioList &playlist, int index = 0);

    Audio * audioAt(int index);
    Audio * currentAudio();

public slots:
    void setVolume(int volume);
    void setPosition(int position);

    void setLoop(bool loop);
    void setShuffle(bool shuffle);

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

    bool bassCreate();
    bool bassFree();
    bool bassCreateStream(Audio *audio);
    bool bassFreeStream();
    bool bassValidStream();
    bool bassSetVolume(int volume);
    bool bassSetPosition(int position);
    bool bassPlay();
    bool bassPause();

    void log(const QString &message);

    bool validIndex(int index);

    void switchOrPause(int index);
    int nextIndex();
    int backIndex();

    void shuffle();
    void unshuffle();

    void setAudio(int index);

    QList<AudioPosition> m_playlist;
    Timer *pm_timer;
    HSTREAM m_stream;
    int m_index;
    int m_volume;
    bool m_loop;
    bool m_shuffle;
    bool m_playing;
};

#endif // PLAYER_HPP
