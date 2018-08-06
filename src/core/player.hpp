#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QApplication>
#include <QObject>
#include <QTimer>

#include "audio.hpp"
#include "bass.hpp"
#include "config.hpp"
#include "playlist.hpp"

#define ePlayer (Player::instance())

class Player : public QObject
{
    Q_OBJECT

public:
    Player(QObject *parent = nullptr);
    ~Player();

    static Player * instance();

    Playlist * playlist();

    bool isPlaying() const;
    bool isPaused() const;

    void setVolume(int volume);
    int volume() const;

    void setPosition(int position);
    int position();

    void play();
    void pause();

    void createPlaylist(Audios *audios, int index = 0);

signals:
    void audioChanged(Audio *audio);
    void stateChanged();
    void positionChanged(int position);
    void volumeChanged(int volume);

private slots:
    void onPlaylistIndexChanged(int index);
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
