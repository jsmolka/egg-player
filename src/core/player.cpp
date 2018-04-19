#include "player.hpp"

/*
 * Constructor.
 *
 * :param parent: pointer of parent object
 */
Player::Player(QObject *parent) : QObject(parent)
{
    qsrand(time(0));

    if (!BASS_Init(-1, 44100, 0, 0, NULL))
        Logger::log("Player: Cannot initialize BASS");

    m_stream = 0;
    m_channel = 0;
    m_index = -1;
    m_volume = 0;
    m_loop = false;
    m_shuffled = false;
    m_playing = false;

    pm_timer = new Timer(1000, this);

    connect(pm_timer, SIGNAL(timeout(qint64)), this, SLOT(onTimeout(qint64)));
}

/*
 * Destructor.
 */
Player::~Player()
{
    if (!BASS_Free())
        Logger::log("Player: Cannot free BASS");
}

void Player::setIndex(int index)
{
    m_index = index;
    if (index != -1)
        setActiveAudio(index);
}

int Player::index() const
{
    return m_index;
}

bool Player::isLoop() const
{
    return m_loop;
}

bool Player::isShuffled() const
{
    return m_shuffled;
}

/*
 * Getter for player volume.
 *
 * :return: volume
 */
int Player::volume() const
{
    float volume;
    BASS_ChannelGetAttribute(m_stream, BASS_ATTRIB_VOL, &volume);
    return (int) volume * VOLUME_FACTOR;
}

int Player::position() const
{
    return pm_timer->total() / 1000;
}

bool Player::isPlaying() const
{
    return m_playing;
}

void Player::setAudioList(const AudioList &audioList)
{
    m_index = -1;
    m_shuffled = false;
    m_playing = false;

    m_playlist.clear();

    for (int i = 0; i < audioList.size(); i++)
        m_playlist << AudioPosition(i, audioList[i]);
}

Audio * Player::audioAt(int index)
{
    return m_playlist[index].audio;
}

Audio * Player::currentAudio()
{
    return audioAt(m_index);
}

/*
 * Calculates the next playlist index based
 * on playlist size and loop property. Returns
 * -1 if there is no next index.
 *
 * :return: next index
 */
int Player::nextIndex()
{
    if (m_index == -1)
        return -1;

    if (m_index == m_playlist.size() - 1)
        return m_loop ? 0 : -1;

    return ++m_index;
}

/*
 * Calculates the previous playlist index based
 * on playlist size and loop property. Returns
 * -1 if there is no previuos index.
 *
 * :return: previous index
 */
int Player::backIndex()
{
    if (m_index == -1)
        return -1;

    if (m_index == 0)
        return m_loop ? m_playlist.size() - 1 : -1;

    return --m_index;
}

/*
 * Setter for player volume. Should be between 0 and 100.
 * The volume gets divided by VOLUME_FACTOR to get the
 * float value necessary for BASS.
 *
 * :param volume: volume
 * :emit: volumeChanged
 */
void Player::setVolume(int volume)
{
    m_volume = volume;
    volume = qMin(100, qMax(volume, 0));
    BASS_ChannelSetAttribute(m_stream, BASS_ATTRIB_VOL, (float) volume / VOLUME_FACTOR);
    emit volumeChanged(volume);
}

void Player::setPosition(int position)
{
    if (m_index != -1)
    {
        emit positionChanged(position);

        position *= (qint64) 1000;
        //pm_player->setPosition(position);
        pm_timer->setTotal(position);
    }
}

/*
 * Setter for loop property.
 *
 * :param loop: player loop
 */
void Player::setLoop(bool loop)
{
    m_loop = loop;
}

/*
 * Setter for shuffle property. Shuffles
 * or unshuffles (sorts) the playlist
 * if an index is set.
 *
 * :param shuffled: shuffle or unshuffle
 */
void Player::setShuffled(bool shuffled)
{
    if (m_shuffled != shuffled && m_index != -1)
    {
        if (shuffled)
            shuffle();
        else
            unshuffle();
    }
}

/*
 * Plays or resumes the current audio.
 *
 * :param restart: restart stream, default false
 * :emit: TODO: What does it emit?
 */
void Player::play(bool restart)
{
    if (!BASS_ChannelPlay(m_stream, restart))
        Logger::log(QString("Player: Cannot play stream: '%1'").arg(currentAudio()->path()));
    pm_timer->start();
    setState(true);
}

/*
 * Pauses the current stream.
 *
 * :emit: TODO: What does it emit?
 */
void Player::pause()
{
    if (!BASS_ChannelPause(m_stream))
        Logger::log(QString("Player: Cannot pause stream: '%1'").arg(currentAudio()->path()));
    pm_timer->pause();
    setState(false);
}

void Player::next()
{
    int index = nextIndex();
    if (index != -1)
    {
        m_index = index;
        setActiveAudio(index);
    }
    else
    {
        pause();
        setPosition(0);
    }
}

void Player::back()
{
    int index = backIndex();
    if (index != -1)
    {
        m_index = index;
        setActiveAudio(index);
    }
}

void Player::onTimeout(qint64 total)
{
    total = total / 1000;
    // Prevent showing one extra second after end
    if (total <= currentAudio()->length())
        emit positionChanged(total);
}

void Player::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::LoadingMedia)
    {
        if (m_index != -1)
            emit audioChanged(currentAudio());
    }
    else if (status == QMediaPlayer::LoadedMedia)
    {
        pm_timer->restart();
        if (m_playing)
            play();
    }
    else if (status == QMediaPlayer::EndOfMedia)
    {
        next();
    }
}

void Player::shuffle()
{
    Audio * audio = currentAudio();

    std::random_shuffle(m_playlist.begin(), m_playlist.end());

    // Put current audio at the front
    for (int i = 0; i < m_playlist.size(); i++)
    {
        if (audio == audioAt(i))
        {
            m_playlist.swap(0, i);
            break;
        }
    }
    m_index = 0;
    m_shuffled = true;
}

void Player::unshuffle()
{
    Audio *audio = currentAudio();

    std::sort(m_playlist.begin(), m_playlist.end(),
        [](const AudioPosition &ap1, const AudioPosition &ap2) {return ap1.index < ap2.index;});

    // Find index of current audio
    for (int i = 0; i < m_playlist.size(); i++)
    {
        if (audio == audioAt(i))
        {
            m_index = i;
            break;
        }
    }
    m_shuffled = false;
}

void Player::setActiveAudio(int index)
{
    // Free old stream if it exists
    if (m_stream != 0)  // TODO: Check differently
        if (!BASS_StreamFree(m_stream))
            Logger::log("Failed freeing BASS stream");

    // Create stream and get current channel
    m_stream = BASS_StreamCreateFile(false, audioAt(index)->path().toLatin1(), 0, 0, 0);
    m_channel = BASS_SampleGetChannel(m_stream, false);  // TODO: not needed???

    // Set volume for newly created stream
    setVolume(m_volume);

    setPosition(0);
}

void Player::setState(bool playing)
{
    m_playing = playing;
    emit stateChanged(playing);
}
