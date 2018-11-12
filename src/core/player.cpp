#include "player.hpp"

#include "core/config.hpp"
#include "core/macros.hpp"

Player::Player(QObject *parent)
    : QObject(parent)
    , m_playlist(this)
    , m_updateTimer(this)
    , m_playing(false)
    , m_volume(0)
    , m_position(-1)
{
    connect(&m_updateTimer, &QTimer::timeout, this, &Player::update);
    connect(&m_playlist, &Playlist::indexChanged, this, &Player::onPlaylistIndexChanged);

    m_updateTimer.start(cfg_player.updateInterval());

    m_bass.sync().setFunction([](void *data) {
        Player *player = static_cast<Player *>(data);
        player->playlist().next();
    });
    m_bass.sync().setFunctionData(this);
}

const Playlist &Player::playlist() const
{
    return m_playlist;
}

Playlist &Player::playlist()
{
    return EGG_REF_CAST(Player, Playlist, playlist);
}

bool Player::isPlaying() const
{
    return m_playing;
}

int Player::volume() const
{
    return m_volume;
}

int Player::position()
{
    return m_bass.stream().position();
}

void Player::play()
{
    if (m_bass.stream().play())
    {
        m_playing = true;
        emit stateChanged();
    }
}

void Player::pause()
{
    if (m_bass.stream().pause())
    {
        m_playing = false;
        emit stateChanged();
    }
}

void Player::createPlaylist(audios::CurrentState *state, int index)
{
    m_playlist.setIndex(index);
    m_playlist.create(state);

    setAudio(m_playlist.currentAudio());
}

void Player::setVolume(int volume)
{
    volume = qBound(0, volume, 100);
    float volf = static_cast<float>(volume);
    float quof = static_cast<float>(cfg_player.volumeQuotient());
    m_volume = volume;

    if (!m_bass.stream().setVolume(volf / quof))
        return;

    emit volumeChanged(volume);
}

void Player::setPosition(int position)
{
    if (m_bass.stream().setPosition(position))
        emit positionChanged(position);
}

void Player::onPlaylistIndexChanged(int index)
{
    if (index == -1)
    {
        pause();
        setPosition(0);
    }
    else
    {
        setAudio(m_playlist.audioAt(index));
    }
}

void Player::update()
{
    if (!isPlaying())
        return;

    const int position = this->position();
    if (position != m_position)
    {
        m_position = position;
        emit positionChanged(position);
    }
}

void Player::setAudio(Audio *audio)
{
    if (!audio || !m_bass.stream().create(audio))
        return;

    m_bass.sync().setSync(m_bass.stream().handle());
    setVolume(m_volume);

    if (m_playing)
        play();
    else
        pause();

    emit audioChanged(audio);
    emit positionChanged(0);
}
