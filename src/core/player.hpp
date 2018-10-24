#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QObject>
#include <QTimer>

#include "core/audio.hpp"
#include "core/globals.hpp"
#include "core/playlist.hpp"
#include "core/bass/bass.hpp"

#define ePlayer (Player::instance())

class Player : public QObject
{
    Q_OBJECT

public:
    explicit Player(QObject *parent = nullptr);

    static Player *instance();

    Playlist &playlist();

    bool isPlaying() const;
    bool isPaused() const;

    int volume() const;
    int position();

    void createPlaylist(Audios *audios, int index = 0);

public slots:
    void setVolume(int volume);
    void setPosition(int position);

    void increaseVolume();
    void decreaseVolume();

    void play();
    void pause();
    void toggleState();

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

    void setAudio(Audio *audio);

    Playlist m_playlist;
    QTimer m_updateTimer;
    Bass m_bass;
    int m_volume;
    int m_position;
    bool m_playing;
};

#endif // PLAYER_HPP
