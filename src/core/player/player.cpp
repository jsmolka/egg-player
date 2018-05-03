#include "player.hpp"

/*
 * Constructor.
 *
 * :param parent: parent, default nullptr
 */
Player::Player(QObject *parent) :
    QObject(parent)
{
    qsrand(time(0));

    bassCreate();
    m_stream = 0;
    m_index = -1;
    m_volume = 0;
    m_loop = false;
    m_shuffle = false;
    m_playing = false;
    pm_timer = new Timer(1000, this);

    connect(pm_timer, SIGNAL(timeout(qint64)), this, SLOT(onTimeout(qint64)));

    pm_instance = this;
}

/*
 * Destructor.
 */
Player::~Player()
{
    bassFree();
}

/*
 * Returns the current player instance. It always
 * returns the most recent player.
 *
 * :return: player
 */
Player * Player::instance()
{
    return pm_instance;
}

/*
 * Setter for index property.
 *
 * :param index: index
 */
void Player::setIndex(int index)
{
    m_index = index;

    if (!validIndex(m_index))
        return;

    setAudio(m_index);
}

/*
 * Getter for index property.
 *
 * :return: index
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
 * Getter for shuffle property.
 *
 * :return: shuffle
 */
bool Player::isShuffle() const
{
    return m_shuffle;
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
 * Getter for volume property.
 *
 * :return: volume
 */
int Player::volume() const
{
    return m_volume;
}

/*
 * Getter for position. The remaining time is not
 * needed because it would be removed by the
 * integer division anyway.
 *
 * :return: position in seconds
 */
int Player::position() const
{
    return pm_timer->elapsed() / 1000;
}

/*
 * Loads playlist for player. It first clears the
 * the current playlist and then adds all audios.
 * After that it shuffles the playlist if the
 * shuffle property is true.
 *
 * :param audios: audios
 * :param index: index, default 0
 */
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

/*
 * Gets audio at index.
 *
 * :param index: index
 * :return: audio, nullptr if invalid index
 */
Audio * Player::audioAt(int index)
{
    if (!validIndex(index))
        return nullptr;

    return m_playlist[index].audio;
}

/*
 * Gets current audio.
 *
 * :return: audio, nullptr if invalid index
 */
Audio * Player::currentAudio()
{
    return audioAt(m_index);
}

/*
 * Gets index at index.
 *
 * :param index: index
 * :return: index, -1 if invalid index
 */
int Player::indexAt(int index)
{
    if (!validIndex(index))
        return -1;

    return m_playlist[index].index;
}

/*
 * Gets current index.
 *
 * :return: index, -1 if invalid index
 */
int Player::currentIndex()
{
    return indexAt(m_index);
}

/*
 * Setter for volume property. Volume should be
 * between 0 and 100.
 *
 * :param volume: volume
 * :emit volumeChanged: volume
 */
void Player::setVolume(int volume)
{
    volume = qMin(100, qMax(volume, 0));
    if (volume == m_volume)
        return;

    m_volume = volume;

    bassSetVolume(m_volume);

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
    if (this->position() == position)
        return;

    if (!bassSetPosition(position))
        return;

    pm_timer->setElapsed(position * 1000);

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
 * Setter for shuffle property. The playlist can
 * only be shuffled or unshuffled if the player
 * has a valid index.
 *
 * :param shuffle: shuffle
 */
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

/*
 * Plays the current stream.
 *
 * :emit stateChanged: state
 */
void Player::play()
{
    if (!bassPlay())
        return;

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
    if (!bassPause())
        return;

    m_playing = false;
    pm_timer->pause();

    emit stateChanged(State::Paused);
}

/*
 * Switches to the next song in the playlist. If
 * there is not next song the position gets reset
 * and the stream gets paused.
 */
void Player::next()
{
    switchOrPause(nextIndex());
}

/*
 * Switches to the previous song in the playlist.
 * If there is not previous song the position
 * gets reset and the stream gets paused.
 */
void Player::previous()
{
    switchOrPause(previousIndex());
}

/*
 * Slot for timer timeout. It emits the current
 * position and manages automatically playing
 * the next song if the current one finishes.
 *
 * :param elapsed: elapsed time in milliseconds
 * :emit positionChanged: position in seconds
 */
void Player::onTimeout(qint64 elapsed)
{
    Audio *audio = currentAudio();
    if (!audio)
        return;

    elapsed = elapsed / 1000;
    if (elapsed <= audio->length())
        emit positionChanged(elapsed);
    else
        next();
}

/*
 * Initializes BASS.
 *
 * :return: success
 */
bool Player::bassCreate()
{

    if (!BASS_Init(-1, 44100, 0, 0, NULL))
    {
        logAudio("Player: Cannot initialize BASS");
        return false;
    }
    return true;
}

/*
 * Frees BASS.
 *
 * :return: success
 */
bool Player::bassFree()
{
    if (!BASS_Free())
    {
        logAudio("Player: Cannot free BASS");
        return false;
    }
    return true;
}

/*
 * Creates a BASS stream from an audio. If the
 * stream is currently occupied it gets freed
 * before reassigning.
 *
 * :param audio: audio
 * :return: success
 */
bool Player::bassCreateStream(Audio *audio)
{
    if (bassValidStream())
        if (!bassFreeStream())
            return false;

    m_stream = BASS_StreamCreateFile(false, audio->path().toLatin1(), 0, 0, 0);
    return bassValidStream();
}

/*
 * Frees the stream if it is assigned.
 *
 * :return: success
 */
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

/*
 * Checks if the current stream is valid.
 *
 * :return: valid
 */
bool Player::bassValidStream()
{
    return m_stream == 0 ? false : true;
}

/*
 * Sets the volume of the current channel. The
 * volume gets divided to get the float value
 * BASS needs.
 * The quotient is 1000 which seems to be a
 * reasonable value. For a higher volume ceiling
 * this value should be lowered.
 *
 * :param volume: volume
 * :return: success
 */
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

/*
 * Sets position of BASS channel.
 *
 * :param position: position
 * :return: success
 */
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

/*
 * Plays the current stream.
 *
 * :return: success
 */
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

/*
 * Pauses the current stream.
 *
 * :return: success
 */
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

/*
 * Small function for logging purposes. If there
 * is a current audio it gets added to the
 * message.
 *
 * :param message: message
 */
void Player::logAudio(const QString &message)
{
    QString log = message;

    Audio *audio = currentAudio();
    if (audio)
        log.append(QString(" '%1'").arg(audio->path()));

    Logger::log(log);
}

/*
 * Checks if an index is valid.
 *
 * :return: valid
 */
bool Player::validIndex(int index)
{
    return !(index < 0 || index >= m_playlist.size());
}

/*
 * Smoothly switches to an index and pauses if
 * the index is invalid.
 *
 * :param index: index
 */
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

/*
 * Calculates the next playlist index.
 *
 * :return: index, -1 if last and no loop
 */
int Player::nextIndex()
{
    if (!validIndex(m_index))
        return -1;

    if (m_index == m_playlist.size() - 1)
        return m_loop ? 0 : -1;

    return ++m_index;
}

/*
 * Calculates the previous playlist index.
 *
 * :return: index, -1 if first and no loop
 */
int Player::previousIndex()
{
    if (!validIndex(m_index))
        return -1;

    if (m_index == 0)
        return m_loop ? m_playlist.size() - 1 : -1;

    return --m_index;
}

/*
 * Shuffles the playlist and swaps the current
 * audio with first audio. Because of that the
 * full shuffled playlist is pending.
 */
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

/*
 * Unshuffles the playlist and sets the current
 * index to the current audio. Because of that
 * the audio is in the current position inside
 * the unshuffled playlist.
 */
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

/*
 * Sets active audio. This involves freeing the
 * current stream, creating a new one, setting
 * the volume and restarting the timer. If the
 * player is was previouly playing it gets
 * started automatically, otherwise it pauses.
 *
 * :param index: audio index
 * :emit audioChanged: audio
 * :emit positionChanged: position
 */
void Player::setAudio(int index)
{
    bassFreeStream();

    Audio *audio = audioAt(index);
    if (!audio)
        return;

    if (!bassCreateStream(audio))
        return;

    setVolume(m_volume);
    pm_timer->restart();

    if (m_playing)
        play();
    else
        pause();

    emit audioChanged(audio);
    emit positionChanged(0);
}

/*
 * Holds the current player instance.
 */
Player * Player::pm_instance = nullptr;
