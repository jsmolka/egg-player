#include "player.hpp"

#include "core/config.hpp"
#include "core/macros.hpp"

Player::Player(QObject *parent)
    : QObject(parent)
    , m_playlist(this)
    , m_updateTimer(this)
    , m_volume(0)
    , m_position(-1)
    , m_playing(false)
{
    connect(&m_updateTimer, &QTimer::timeout, this, &Player::update);
    connect(&m_playlist, &Playlist::indexChanged, this, &Player::onPlaylistIndexChanged);

    m_updateTimer.start(cfg_player.updateInterval());
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

bool Player::isPaused() const
{
    return !m_playing;
}

int Player::volume() const
{
    return m_volume;
}

int Player::position()
{
    return m_bass.stream().isHandleValid() ? m_bass.stream().position() : -1;
}

void Player::play()
{
    if (m_bass.stream().isHandleValid())
        if (!m_bass.stream().play())
            return;

    m_playing = true;
    emit stateChanged();
}

void Player::pause()
{
    if (m_bass.stream().isHandleValid())
        if (!m_bass.stream().pause())
            return;

    m_playing = false;
    emit stateChanged();
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
    if (m_bass.stream().isHandleValid())
        if (!m_bass.stream().setVolume(static_cast<float>(volume) / static_cast<float>(cfg_player.volumeQuotient())))
            return;

    m_volume = volume;
    emit volumeChanged(volume);
}

void Player::setPosition(int position)
{
    if (m_bass.stream().isHandleValid())
        if (!m_bass.stream().setPosition(position))
            return;

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
    if (!m_playing || !m_bass.stream().isHandleValid())
        return;

    const int position = this->position();
    if (position != m_position)
    {
        m_position = position;
        emit positionChanged(position);
    }
}

void Player::callback(HSYNC handle, DWORD channel, DWORD data, void *user)
{
    Q_UNUSED(handle);
    Q_UNUSED(channel);
    Q_UNUSED(data);

    Player *player = static_cast<Player *>(user);
    player->playlist().next();
}

void Player::setAudio(Audio *audio)
{
    if (!audio || !m_bass.stream().create(audio))
        return;

    m_bass.stream().setCallback(callback, this);
    setVolume(m_volume);

    if (m_playing)
        play();
    else
        pause();

    emit audioChanged(audio);
    emit positionChanged(0);
}
