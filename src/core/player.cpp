#include "player.hpp"

Player::Player(QObject *parent)
    : QObject(parent)
    , m_timer(this)
    , m_index(-1)
    , m_volume(0)
    , m_position(-1)
    , m_loop(false)
    , m_shuffle(false)
    , m_playing(false)
{
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer.start(cfgPlayer->updateInterval());
}

Player::~Player()
{

}

Player * Player::instance()
{
    if (!_instance)
        _instance = new Player(qApp);

    return _instance;
}

void Player::setIndex(int index)
{
    m_index = index;
    setAudio(index);
}

int Player::index() const
{
    return m_index;
}

bool Player::isLoop() const
{
    return m_loop;
}

bool Player::isShuffle() const
{
    return m_shuffle;
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
    return m_bass.stream()->isValid() ? m_bass.stream()->position() : -1;
}

void Player::loadPlaylist(const Audios &audios, int index)
{
    m_playing = false;
    m_playlist.clear();
    m_playlist.reserve(audios.size());

    for (int i = 0; i < audios.size(); i++)
        m_playlist << PlaylistItem(i, audios[i]);

    setIndex(index);
    setShuffle(m_shuffle);
}

Audio * Player::audioAt(int index)
{
    return validIndex(index) ? m_playlist[index].audio : nullptr;
}

Audio * Player::currentAudio()
{
    return audioAt(m_index);
}

void Player::setVolume(int volume)
{
    volume = qMax(0, qMin(volume, 100));
    if (m_bass.stream()->isValid())
        if (!m_bass.stream()->setVolume(static_cast<float>(volume) / 1000.0))
            return;

    m_volume = volume;
    emit volumeChanged(volume);
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
    m_loop = loop;
}

void Player::setShuffle(bool shuffle)
{
    if (shuffle)
        this->shuffle();
    else
        unshuffle();

    m_shuffle = shuffle;
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
    switchOrPause(nextIndex());
}

void Player::previous()
{
    switchOrPause(previousIndex());
}

void Player::update()
{
    if (!m_bass.stream()->isValid())
        return;

    int position = this->position();
    if (position != m_position)
    {
        m_position = position;
        emit positionChanged(position);
    }

    if (m_bass.stream()->isStopped())
        next();
}

bool Player::validIndex(int index)
{
    return index > -1 && index < m_playlist.size();
}

void Player::switchOrPause(int index)
{
    if (validIndex(index))
    {
        setIndex(index);
    }
    else
    {
        pause();
        setPosition(0);
    }
}

int Player::nextIndex()
{
    if (!validIndex(m_index))
        return -1;

    if (m_index == m_playlist.size() - 1)
        return m_loop ? 0 : -1;

    return ++m_index;
}

int Player::previousIndex()
{
    if (!validIndex(m_index))
        return -1;

    if (m_index == 0)
        return m_loop ? m_playlist.size() - 1 : -1;

    return --m_index;
}

void Player::shuffle()
{
    std::random_shuffle(m_playlist.begin(), m_playlist.end());

    for (int i = 0; i < m_playlist.size(); i++)
    {
        if (currentAudio() == audioAt(i))
        {
            std::swap(m_playlist[0], m_playlist[i]);
            break;
        }
    }
    m_index = 0;
}

void Player::unshuffle()
{
    std::sort(m_playlist.begin(), m_playlist.end(),
        [](const PlaylistItem &i1, const PlaylistItem &i2) {
            return i1.index < i2.index;
        }
    );

    for (int i = 0; i < m_playlist.size(); i++)
    {
        if (currentAudio() == audioAt(i))
        {
            m_index = i;
            break;
        }
    }
}

void Player::setAudio(int index)
{
    Audio *audio = audioAt(index);
    if (!audio || !m_bass.stream()->create(audio))
        return;

    setVolume(m_volume);

    if (m_playing)
        play();
    else
        pause();

    emit audioChanged(audio);
    emit positionChanged(0);
}

Player * Player::_instance = nullptr;
