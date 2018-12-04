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
    int position() const;

    void play();
    void pause();

public slots:
    void setVolume(int volume);
    void setPosition(int position);

signals:
    void stateChanged();
    void volumeChanged(int volume);
    void positionChanged(int position);
    void audioChanged(Audio audio);

private slots:
    void updatePosition();

    void onPlaylistAudioChanged(Audio audio);
    void onPlaylistEndReached();

private:
    static void syncFunction(void *data);

    void changeAudio(Audio audio);

    void init();

    Bass m_bass;
    Playlist m_playlist;
    QTimer m_timer;
    bool m_playing;
    int m_volume;
    int m_position;
};

#endif // PLAYER_HPP
