#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QApplication>
#include <QObject>
#include <QTimer>

#include "audio.hpp"
#include "bass.hpp"
#include "config.hpp"
#include "playlist.hpp"
#include "types.hpp"

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
    bool isPaused() const;

    int volume() const;
    int position();

    void createPlaylist(const Audios &audios, int index = 0);

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
    void onIndexChanged(int index);
    void update();

private:
    static void CALLBACK callback(HSYNC handle, DWORD channel, DWORD data, void *user);

    void setAudio(int index);

    Playlist m_playlist;
    QTimer m_updateTimer;
    Bass m_bass;
    int m_volume;
    int m_position;
    bool m_playing;
};

#endif // PLAYER_HPP
