#include "player.hpp"

#include <QApplication>

#include "config.hpp"

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

    m_updateTimer.start(cfgPlayer.updateInterval());
}

Player *Player::instance()
{
    static Player *player = new Player(qApp);
    return player;
}

Playlist & Player::playlist()
{
    return m_playlist;
}

bool Player::isPlaying() const
{
    return m_playing;
}

bool Player::isPaused() const
{
    return !m_playing;
}

void Player::setVolume(int volume)
{
    volume = qBound(0, volume, 100);
    if (m_bass.stream().isValid())
        if (!m_bass.stream().setVolume(static_cast<float>(volume) / static_cast<float>(cfgPlayer.volumeQuotient())))
            return;

    m_volume = volume;
    cfgPlayer.setVolume(volume);
    emit volumeChanged(volume);
}

int Player::volume() const
{
    return m_volume;
}

void Player::setPosition(int position)
{
    if (m_bass.stream().isValid())
        if (!m_bass.stream().setPosition(position))
            return;

    emit positionChanged(position);
}

int Player::position()
{
    return m_bass.stream().isValid()
        ? m_bass.stream().position()
        : -1;
}

void Player::play()
{
    if (m_bass.stream().isValid())
        if (!m_bass.stream().play())
            return;

    m_playing = true;
    emit stateChanged();
}

void Player::pause()
{
    if (m_bass.stream().isValid())
        if (!m_bass.stream().pause())
            return;

    m_playing = false;
    emit stateChanged();
}

void Player::toggleState()
{
    if (m_playing)
        pause();
    else
        play();
}

void Player::createPlaylist(Audios *audios, int index)
{
    m_playlist.setIndex(index);
    m_playlist.create(audios);

    setAudio(m_playlist.index());
}

void Player::onPlaylistIndexChanged(int index)
{
    if (index != -1)
    {
        setAudio(index);
    }
    else
    {
        pause();
        setPosition(0);
    }
}

void Player::update()
{
    if (!m_bass.stream().isValid() || !m_playing)
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

void Player::setAudio(int index)
{
    Audio *audio = m_playlist.audioAt(index);
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
