#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QObject>
#include <QTimer>

#include "core/audio.hpp"
#include "core/bass.hpp"
#include "core/playlist.hpp"
#include "core/singleton.hpp"

#define egg_player (Player::instance())

class Player : public QObject, public Singleton<Player>
{
    Q_OBJECT

public:
    explicit Player(QObject *parent = nullptr);

    const Playlist &playlist() const;

    Playlist &playlist();

    bool isPlaying() const;

    int volume() const;
    int position();

    void play();
    void pause();

    void createPlaylist(audios::CurrentState *state, int index = 0);

public slots:
    void setVolume(int volume);
    void setPosition(int position);

signals:
    void stateChanged();
    void volumeChanged(int volume);
    void positionChanged(int position);
    void audioChanged(Audio *audio);

private slots:
    void onPlaylistIndexChanged(int index);
    void update();

private:
    void setAudio(Audio *audio);

    Bass m_bass;
    Playlist m_playlist;
    QTimer m_updateTimer;
    int m_volume;
    int m_position;
};

#endif // PLAYER_HPP
