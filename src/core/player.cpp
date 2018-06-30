#include "player.hpp"

Player::Player(QObject *parent)
    : QObject(parent)
    , m_index(-1)
    , m_volume(0)
    , m_loop(false)
    , m_shuffle(false)
    , m_playing(false)
    , pm_timer(new Timer(1000, this))
{
    connect(pm_timer, SIGNAL(timeout(qint64)), this, SLOT(onTimerTimeout(qint64)));
    connect(pm_timer, SIGNAL(finished()), this, SLOT(onTimerFinished()));
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

    if (!validIndex(m_index))
        return;

    setAudio(m_index);
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

int Player::position() const
{
    return pm_timer->elapsed() / 1000;
}

void Player::loadPlaylist(const Audios &audios, int index)
{
    m_playing = false;
    m_playlist.clear();
    m_playlist.reserve(audios.size());

    for (int i = 0; i < audios.size(); i++)
        m_playlist << AudioPosition(i, audios[i]);

    setIndex(index);

    if (m_shuffle && validIndex(m_index))
        shuffle();
    else
        m_shuffle = false;
}

Audio * Player::audioAt(int index)
{
    Audio *audio = nullptr;

    if (validIndex(index))
        audio = m_playlist[index].audio;

    return audio;
}

Audio * Player::currentAudio()
{
    return audioAt(m_index);
}

int Player::indexAt(int index)
{    
    int idx = -1;

    if (validIndex(index))
        idx = m_playlist[index].index;

    return idx;
}

int Player::currentIndex()
{
    return indexAt(m_index);
}

void Player::setVolume(int volume)
{
    m_volume = qMax(0, qMin(volume, 100));

    if (m_bass.stream()->isValid())
        m_bass.stream()->setVolume(static_cast<float>(m_volume) / 1000.0);

    emit volumeChanged(m_volume);
}

void Player::setPosition(int position)
{
    qint64 ms = position * 1000;
    if (!m_bass.stream()->setPosition(ms))
        return;

    pm_timer->setElapsed(ms);

    emit positionChanged(position);
}

void Player::setLoop(bool loop)
{
    m_loop = loop;
}

void Player::setShuffle(bool shuffle)
{
    if (m_shuffle == shuffle)
        return;

    if (validIndex(m_index))
    {
        if (shuffle)
            this->shuffle();
        else
            unshuffle();
    }
    m_shuffle = shuffle;
}

void Player::play()
{
    if (!m_bass.stream()->play())
        return;

    m_playing = true;
    pm_timer->start(currentAudio()->duration(false));

    emit stateChanged(State::Playing);
}

void Player::pause()
{
    if (!m_bass.stream()->pause())
        return;

    m_playing = false;
    pm_timer->pause();

    emit stateChanged(State::Paused);
}

void Player::next()
{
    switchOrPause(nextIndex());
}

void Player::previous()
{
    switchOrPause(previousIndex());
}

void Player::onTimerTimeout(qint64 elapsed)
{
    Audio *audio = currentAudio();
    if (!audio)
        return;

    emit positionChanged(elapsed / 1000);
}

void Player::onTimerFinished()
{
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
    Audio *audio = currentAudio();
    if (!audio)
        return;

    std::random_shuffle(m_playlist.begin(), m_playlist.end());

    for (int i = 0; i < m_playlist.size(); i++)
    {
        if (audio == audioAt(i))
        {
            std::swap(m_playlist[0], m_playlist[i]);
            break;
        }
    }
    m_index = 0;
}

void Player::unshuffle()
{
    Audio *audio = currentAudio();
    if (!audio)
        return;

    std::sort(m_playlist.begin(), m_playlist.end(),
        [](const AudioPosition &ap1, const AudioPosition &ap2) {
            return ap1.index < ap2.index;
        }
    );

    for (int i = 0; i < m_playlist.size(); i++)
    {
        if (audio == audioAt(i))
        {
            m_index = i;
            break;
        }
    }
}

void Player::setAudio(int index)
{
    if (!m_bass.stream()->free())
        return;

    Audio *audio = audioAt(index);
    if (!audio)
        return;

    if (!m_bass.stream()->create(audio))
        return;

    setVolume(m_volume);
    pm_timer->restart(audio->duration(false));

    if (m_playing)
        play();
    else
        pause();

    emit audioChanged(audio);
    emit positionChanged(0);
}

Player * Player::_instance = nullptr;
