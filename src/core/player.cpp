#include "player.hpp"

/*
 * Constructor.
 *
 * :param parent: parent pointer
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
 * Setter for index property. It also
 * changes the active audio if the index
 * is valid.
 *
 * :param index: index
 */
void Player::setIndex(int index)
{
    m_index = index;
    if (index != -1)
        setAudio(index);
}

/*
 * Getter for index property.
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
 * :return: loop
 */
bool Player::isLoop() const
{
    return m_loop;
}

/*
 * Getter for shuffled property.
 *
 * :return: shuffled
 */
bool Player::isShuffled() const
{
    return m_shuffled;
}

/*
 * Getter for volume property.
 *
 * :return: volume
 */
int Player::volume() const
{
    return m_volume;
}

/*
 * Getter for position.
 *
 * :return: position in seconds
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
 * :return: playing
 */
bool Player::isPlaying() const
{
    return m_playing;
}

/*
 * Sets playlist for player. Iterates over
 * playlist and create audio position to make
 * unshuffeling possible
 *
 * :param playlist: playlist
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
 * :return: audio pointer
 */
Audio * Player::audioAt(int index) const
{
    return m_playlist[index].audio;
}

/*
 * Gets current audio.
 *
 * :return: audio pointer
 */
Audio * Player::currentAudio() const
{
    return audioAt(m_index);
}

/*
 * Setter for volume property. Should be between 0 and 100.
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
 * Setter for position.
 *
 * :param position: position in seconds
 * :emit positionChanged: position in seconds
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
 * :param loop: loop
 */
void Player::setLoop(bool loop)
{
    m_loop = loop;
}

/*
 * Setter for shuffle property. Shuffles
 * or unshuffles (sorts) the playlist.
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
 * :emit stateChanged: state
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
 * :emit stateChanged: state
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
 * Slot for timer timeout. It emits the current
 * position and manages automatically playing
 * the next song if the current one finishes.
 *
 * :param total: current time in milliseconds
 * :emit positionChanged: position in seconds
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
 * :return: index
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
 * :return: index
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
 * Sets active audio. The current stream get freed and a
 * new one get created. The volume for the stream gets set
 * and the timer gets restarded. If the player is in the
 * playing state it player, otherwise it pauses.
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
