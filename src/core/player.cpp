#include "player.hpp"

Player::Player(QObject *parent)
    : QObject(parent)
    , m_playlist(this)
    , m_updateTimer(this)
    , m_volume(0)
    , m_position(-1)
    , m_playing(false)
{
    connect(&m_updateTimer, &QTimer::timeout, this, &Player::update);
    connect(&m_playlist, &Playlist::indexChanged, this, &Player::onIndexChanged);

    m_updateTimer.start(cfgPlayer->updateInterval());
}

Player::~Player()
{

}

Player * Player::instance()
{
    static Player *player = new Player(qApp);
    return player;
}

void Player::setIndex(int index)
{
    m_playlist.setIndex(index);
}

int Player::index() const
{
    return m_playlist.index();
}

bool Player::isLoop() const
{
    return m_playlist.isLoop();
}

bool Player::isShuffle() const
{
    return m_playlist.isShuffle();
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
    return m_bass.stream()->isValid() ? m_bass.stream()->position() : -1;
}

void Player::createPlaylist(const Audios &audios, int index)
{
    m_playlist.setIndex(index);
    m_playlist.loadAudios(audios);

    setAudio(m_playlist.index());
}

Audio * Player::audioAt(int index)
{
    return m_playlist.audioAt(index);
}

Audio * Player::currentAudio()
{
    return m_playlist.currentAudio();
}

void Player::setVolume(int volume)
{
    volume = qMax(0, qMin(volume, 100));
    if (m_bass.stream()->isValid())
        if (!m_bass.stream()->setVolume(static_cast<float>(volume) / 1000.0))
            return;

    m_volume = volume;
    emit volumeChanged(volume);
    cfgPlayer->setVolume(volume);
}

void Player::setPosition(int position)
{
    if (m_bass.stream()->isValid())
        if (!m_bass.stream()->setPosition(position))
            return;

    emit positionChanged(position);
}

void Player::setLoop(bool loop)
{
    m_playlist.setLoop(loop);
    cfgPlayer->setLoop(loop);
}

void Player::setShuffle(bool shuffle)
{
    m_playlist.setShuffle(shuffle);
    cfgPlayer->setShuffle(shuffle);
}

void Player::play()
{
    if (m_bass.stream()->isValid())
        if (!m_bass.stream()->play())
            return;

    m_playing = true;
    emit stateChanged();
}

void Player::pause()
{
    if (m_bass.stream()->isValid())
        if (!m_bass.stream()->pause())
            return;

    m_playing = false;
    emit stateChanged();
}

void Player::next()
{
    m_playlist.next();
}

void Player::previous()
{
    m_playlist.previous();
}

void Player::onIndexChanged(int index)
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
    if (!m_bass.stream()->isValid() || !m_playing)
        return;

    int position = this->position();
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
    player->next();
}

void Player::setAudio(int index)
{
    Audio *audio = audioAt(index);
    if (!audio || !m_bass.stream()->create(audio))
        return;

    m_bass.stream()->setCallback(callback, this);
    setVolume(m_volume);

    if (m_playing)
        play();
    else
        pause();

    emit audioChanged(audio);
    emit positionChanged(0);
}
