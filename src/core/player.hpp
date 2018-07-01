#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QApplication>
#include <QObject>
#include <QTimer>

#include "audio.hpp"
#include "bass.hpp"
#include "config.hpp"

#define ePlayer (Player::instance())

class Player : public QObject
{
    Q_OBJECT

public:
    Player(QObject *parent = nullptr);
    ~Player();

    static Player * instance();

    void setIndex(int index);
    int index() const;

    bool isLoop() const;
    bool isShuffle() const;
    bool isPlaying() const;

    int volume() const;
    int position();

    void loadPlaylist(const Audios &audios, int index = 0);

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
    void previous();

signals:
    void audioChanged(Audio *audio);
    void stateChanged();
    void positionChanged(int position);
    void volumeChanged(int volume);

private slots:
    void update();

private:
    struct PlaylistItem
    {
        PlaylistItem(int index = 0, Audio *audio = nullptr) :
            index(index), audio(audio) {}

        int index;
        Audio *audio;
    };

    bool validIndex(int index);

    void switchOrPause(int index);
    int nextIndex();
    int previousIndex();

    void shuffle();
    void unshuffle();

    void setAudio(int index);

    QVector<PlaylistItem> m_playlist;
    QTimer m_timer;
    Bass m_bass;
    int m_index;
    int m_volume;
    int m_position;
    bool m_loop;
    bool m_shuffle;
    bool m_playing;

    static Player *_instance;
};

#endif // PLAYER_HPP
