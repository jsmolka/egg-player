#include "player.hpp"

#include "core/config.hpp"
#include "core/macros.hpp"

Player::Player(QObject *parent)
    : QObject(parent)
    , m_playlist(this)
    , m_timer(this)
    , m_playing(false)
    , m_volume(0)
    , m_position(-1)
{
    init();

    connect(&m_timer, &QTimer::timeout, this, &Player::updatePosition);
    connect(&m_playlist, &Playlist::audioChanged, this, &Player::onPlaylistAudioChanged);
    connect(&m_playlist, &Playlist::endReached, this, &Player::onPlaylistEndReached);
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

int Player::position() const
{
    return m_position;
}

void Player::play()
{
    if (!m_bass.play())
        return;

    m_timer.start(cfg_player.updateInterval());
    m_playing = true;
    emit stateChanged();
}

void Player::pause()
{
    if (!m_bass.pause())
        return;

    m_timer.stop();
    m_playing = false;
    emit stateChanged();
}

void Player::setVolume(int volume)
{
    volume = qBound(0, volume, 100);
    const float vol = static_cast<float>(volume);
    const float quo = static_cast<float>(cfg_player.volumeQuotient());

    m_bass.setVolume(vol / quo);

    m_volume = volume;
    emit volumeChanged(volume);
}

void Player::setPosition(int position)
{
    if (m_bass.setPosition(position))
    {
        m_position = position;
        emit positionChanged(position);
    }
}

void Player::updatePosition()
{
    const int position = m_bass.position();
    if (position == m_position)
        return;

    m_position = position;
    emit positionChanged(position);
}

void Player::onPlaylistAudioChanged(Audio audio)
{
    changeAudio(audio);
}

void Player::onPlaylistEndReached()
{
    pause();
    setPosition(0);
}

void Player::syncFunction(void *data)
{
    Player *player = static_cast<Player *>(data);
    player->playlist().next();
}

void Player::changeAudio(Audio audio)
{
    if (!m_bass.create(audio))
        return;

    m_bass.applySync();

    setVolume(m_volume);

    if (m_playing)
        play();
    else
        pause();

    emit audioChanged(audio);
    emit positionChanged(0);
}

void Player::init()
{
    m_bass.sync().setFunction(syncFunction);
    m_bass.sync().setFunctionData(this);
}
