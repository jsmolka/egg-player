#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QMediaPlayer>
#include <QMediaPlaylist>
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

    void setIndex(int index);
    int index() const;

    bool isLoop() const;
    bool isShuffled() const;

    int volume() const;
    int position() const;

    bool isPlaying() const;

    void setAudioList(const AudioList &audioList);

    Audio * audioAt(int index);
    Audio * currentAudio();

    int nextIndex();
    int backIndex();

public slots:
    void setVolume(int volume);
    void setPosition(int position);

    void setLoop(bool loop);
    void setShuffled(bool shuffled);

    void play(bool restart = false);
    void pause();
    void next();
    void back();

signals:
    void audioChanged(Audio *audio);
    void stateChanged(bool playing);
    void positionChanged(int position);
    void volumeChanged(int volume);

private slots:
    void onTimeout(qint64 total);
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);

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

    void shuffle();
    void unshuffle();

    void setActiveAudio(int index);
    void setState(bool playing);

    const int VOLUME_FACTOR = 500;

    QList<AudioPosition> m_playlist;
    Timer *pm_timer;
    HSTREAM m_stream;
    HCHANNEL m_channel;
    int m_index;
    int m_volume;
    bool m_loop;
    bool m_shuffled;
    bool m_playing;
};

#endif // PLAYER_HPP
