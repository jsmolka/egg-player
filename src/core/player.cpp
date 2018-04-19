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

/*
 * Setter for current index. It also
 * changes the active audio if the index
 * is valid.
 */
void Player::setIndex(int index)
{
    m_index = index;
    if (index != -1)
        setAudio(index);
}

/*
 * Getter for current index.
 *
 * :return: current index
 */
int Player::index() const
{
    return m_index;
}

/*
 * Getter for loop property.
 *
 * :return: player is looping
 */
bool Player::isLoop() const
{
    return m_loop;
}

/*
 * Getter for shuffled property.
 *
 * :return: player is shuffled
 */
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
    return m_volume;
}

/*
 * Getter for player position.
 *
 * :return: current position in seconds
 */
int Player::position() const
{
    // Could use interval and remaining time aswell
    // but they would be removed by the division anyway
    return pm_timer->total() / 1000;
}

/*
 * Getter for playing property.
 *
 * :return: is player playing
 */
bool Player::isPlaying() const
{
    return m_playing;
}

/*
 * Sets playlist for player.
 *
 * :param playlist: playlist to use
 */
void Player::setPlaylist(const AudioList &playlist)
{
    freeStream();

    m_index = -1;
    m_shuffled = false;
    m_playing = false;

    m_playlist.clear();

    for (int i = 0; i < playlist.size(); i++)
        m_playlist << AudioPosition(i, playlist[i]);
}

/*
 * Gets audio for index.
 *
 * :return: pointer to audio
 */
Audio * Player::audioAt(int index) const
{
    return m_playlist[index].audio;
}

/*
 * Gets current audio.
 *
 * :return: pointer to current audio
 */
Audio * Player::currentAudio() const
{
    return audioAt(m_index);
}

/*
 * Setter for player volume. Should be between 0 and 100.
 * The volume gets divided by 1000 (empirical) to get the
 * float value necessary for BASS.
 *
 * :param volume: volume
 * :emit volumeChanged: volume
 */
void Player::setVolume(int volume)
{
    m_volume = qMin(100, qMax(volume, 0));

    if (m_stream == 0)
        return;

    if (!BASS_ChannelSetAttribute(m_stream, BASS_ATTRIB_VOL, (float) m_volume / 1000))
        Logger::log("Player: Cannot set volume");

    emit volumeChanged(m_volume);
}

/*
 * Setter for player position.
 *
 * :param position: position in seconds
 * :emit: positionChanged
 */
void Player::setPosition(int position)
{
    if (m_index == -1)
        return;

    QWORD bytes = BASS_ChannelSeconds2Bytes(m_stream, double (position));
    if (!BASS_ChannelSetPosition(m_stream, bytes, 0))
        Logger::log("Player: Cannot set position");
    pm_timer->setTotal(position * 1000);

    emit positionChanged(position);
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
 * :param shuffled: shuffled
 */
void Player::setShuffled(bool shuffled)
{
    if (m_shuffled == shuffled || m_index == -1)
        return;

    if (shuffled)
        shuffle();
    else
        unshuffle();
}

/*
 * Plays or resumes the current audio.
 *
 * :emit stateChanged: current state
 */
void Player::play()
{
    if (m_stream == 0
            || BASS_ChannelIsActive(m_stream) == BASS_ACTIVE_PLAYING)
        return;

    if (!BASS_ChannelPlay(m_stream, false))
        Logger::log("Player: Cannot play stream");

    m_playing = true;
    pm_timer->start();

    emit stateChanged(State::Playing);
}

/*
 * Pauses the current stream.
 *
 * :emit stateChanged: current state
 */
void Player::pause()
{
    if (m_stream == 0
            || BASS_ChannelIsActive(m_stream) == BASS_ACTIVE_STOPPED
            || BASS_ChannelIsActive(m_stream) == BASS_ACTIVE_PAUSED)
        return;

    if (!BASS_ChannelPause(m_stream))
        Logger::log("Player: Cannot pause stream");

    m_playing = false;
    pm_timer->pause();

    emit stateChanged(State::Paused);
}

/*
 * Plays the next song in the playlist
 * or stops if nextIndex returns -1.
 */
void Player::next()
{
    int index = nextIndex();
    if (index != -1)
    {
        m_index = index;
        setAudio(index);
    }
    else
    {
        pause();
        setPosition(0);
    }
}

/*
 * Plays the previous song in the playlist
 * or stops if previousIndex returns -1.
 */
void Player::back()
{
    int index = backIndex();
    if (index != -1)
    {
        m_index = index;
        setAudio(index);
    }
    else
    {
        pause();
        setPosition(0);
    }
}

/*
 * Slot for timer timeout. It also manages
 * playing the next audio if the current
 * one finishes.
 *
 * :param total: elapsed time in ms
 * :emit: positionChanged
 */
void Player::onTimeout(qint64 total)
{
    total = total / 1000;

    if (total <= currentAudio()->length())
        emit positionChanged(total);
    else
        next();
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
 * Shuffles current playlist and swaps
 * current audio with first index.
 */
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

/*
 * Unshuffles (sorts) current playlist
 * and sets index to current audio.
 */
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

/*
 * Frees current stream if it exists.
 */
void Player::freeStream()
{
    if (m_stream == 0)
        return;

    if (!BASS_StreamFree(m_stream))
        Logger::log("Player: Cannot free stream '%1'", currentAudio()->path());

    m_stream = 0;
}

/*
 * Sets active audio.
 *
 * :param index: index of audio
 * :emit audioChanged: current audio
 * :emit positionChanged: reset position
 */
void Player::setAudio(int index)
{
    freeStream();
    m_stream = BASS_StreamCreateFile(false, audioAt(index)->path().toLatin1(), 0, 0, 0);

    if (m_stream == 0)
        Logger::log("Player: Cannot create stream '%1'", currentAudio()->path());

    setVolume(m_volume);
    pm_timer->restart();

    if (m_playing)
        play();
    else
        pause();

    emit audioChanged(currentAudio());
    emit positionChanged(0);
}
