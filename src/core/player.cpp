#include "player.hpp"

Player::Player(QObject *parent)
    : QObject(parent)
    , m_stream(0)
    , m_index(-1)
    , m_volume(0)
    , m_loop(false)
    , m_shuffle(false)
    , m_playing(false)
    , pm_timer(new Timer(1000, this))
{
    qsrand(time(0));

    bassCreate();

    connect(pm_timer, SIGNAL(timeout(qint64)), this, SLOT(onTimerTimeout(qint64)));
    connect(pm_timer, SIGNAL(finished()), this, SLOT(onTimerFinished()));
}

Player::~Player()
{
    bassFree();
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
    if (!bassFreeStream())
        return;

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
    if (!validIndex(index))
        return nullptr;

    return m_playlist[index].audio;
}

Audio * Player::currentAudio()
{
    return audioAt(m_index);
}

int Player::indexAt(int index)
{
    if (!validIndex(index))
        return -1;

    return m_playlist[index].index;
}

int Player::currentIndex()
{
    return indexAt(m_index);
}

void Player::setVolume(int volume)
{
    m_volume = qMax(0, qMin(volume, 100));

    bassSetVolume(m_volume);

    emit volumeChanged(m_volume);
}

void Player::setPosition(int position)
{
    if (!bassSetPosition(position))
        return;

    pm_timer->setElapsed(position * 1000);

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
    if (!bassPlay())
        return;

    m_playing = true;
    pm_timer->start(currentAudio()->duration(false));

    emit stateChanged(State::Playing);
}

void Player::pause()
{
    if (!bassPause())
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

bool Player::bassCreate()
{

    if (!BASS_Init(-1, 44100, 0, 0, NULL))
    {
        logAudio("Player: Cannot initialize BASS");
        return false;
    }
    return true;
}

bool Player::bassFree()
{
    if (!BASS_Free())
    {
        logAudio("Player: Cannot free BASS");
        return false;
    }
    return true;
}

bool Player::bassCreateStream(Audio *audio)
{
    if (bassValidStream())
        if (!bassFreeStream())
            return false;

    m_stream = BASS_StreamCreateFile(false, audio->pathWChar(), 0, 0, 0);
    return bassValidStream();
}

bool Player::bassFreeStream()
{
    if (!bassValidStream())
        return true;

    if (!BASS_StreamFree(m_stream))
    {
        logAudio("Player: Cannot free stream");
        return false;
    }

    m_stream = 0;
    return true;
}

bool Player::bassValidStream()
{
    return m_stream == 0 ? false : true;
}

bool Player::bassSetVolume(int volume)
{
    if (!bassValidStream())
            return false;

    if (!BASS_ChannelSetAttribute(m_stream, BASS_ATTRIB_VOL, (float) volume / 1000))
    {
        logAudio("Player: Cannot set volume");
        return false;
    }
    return true;
}

bool Player::bassSetPosition(int position)
{
    if (!bassValidStream())
        return false;

    QWORD bytes = BASS_ChannelSeconds2Bytes(m_stream, double (position));
    if (!BASS_ChannelSetPosition(m_stream, bytes, 0))
    {
        logAudio("Player: Cannot set position");
        return false;
    }
    return true;
}

bool Player::bassPlay()
{
    if (!bassValidStream())
        return false;

    if (BASS_ChannelIsActive(m_stream) == BASS_ACTIVE_PLAYING)
        return true;

    if (!BASS_ChannelPlay(m_stream, false))
    {
        logAudio("Player: Cannot play stream");
        return false;
    }
    return true;
}

bool Player::bassPause()
{
    if (!bassValidStream())
        return false;

    if (BASS_ChannelIsActive(m_stream) == BASS_ACTIVE_PAUSED
            || BASS_ChannelIsActive(m_stream) == BASS_ACTIVE_STOPPED)
        return true;

    if (!BASS_ChannelPause(m_stream))
    {
        logAudio("Player: Cannot pause stream");
        return false;
    }
    return true;
}

void Player::logAudio(const QString &message)
{
    Audio *audio = currentAudio();
    if (audio)
        log(message + QString(" %1").arg(audio->path()));
    else
        log(message);
}

bool Player::validIndex(int index)
{
    return !(index < 0 || index >= m_playlist.size());
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
    if (!bassFreeStream())
        return;

    Audio *audio = audioAt(index);
    if (!audio)
        return;

    if (!bassCreateStream(audio))
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
