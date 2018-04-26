#include "player.hpp"

/*
 * Constructor.
 *
 * :param parent: parent pointer
 */
Player::Player(QObject *parent) : QObject(parent)
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
}

/*
 * Destructor.
 */
Player::~Player()
{
    bassFree();
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
 * need because it would be removed by the division
 * anyway.
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
 * :param playlist: playlist
 * :param index: index, default 0
 */
void Player::loadPlaylist(const AudioList &playlist, int index)
{
    if (!bassFreeStream())
        return;

    m_playing = false;
    m_playlist.clear();
    m_playlist.reserve(playlist.size());

    for (int i = 0; i < playlist.size(); i++)
        m_playlist << AudioPosition(i, playlist[i]);

    setIndex(index);

    if (m_shuffle && validIndex(m_index))
        shuffle();
    else
        m_shuffle = false;
}

/*
 * Gets audio pointer at index. If the
 * index is invalid it returns a nullptr.
 *
 * :return: audio pointer
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
 * :return: audio pointer
 */
Audio * Player::currentAudio()
{
    return audioAt(m_index);
}

/*
 * Setter for volume property. Volume should
 * be between 0 and 100.
 *
 * :param volume: volume
 * :emit volumeChanged: volume
 */
void Player::setVolume(int volume)
{
    m_volume = qMin(100, qMax(volume, 0));

    if (!bassSetVolume(m_volume))
        return;

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
 * Setter for shuffle property. The playlist
 * can only be shuffled or unshuffled if the
 * player has a valid index.
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
 * Plays or resumes the current audio.
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
 * Switches to the next song in the playlist.
 */
void Player::next()
{
    switchOrPause(nextIndex());
}

/*
 * Switches to the previous song in the playlist.
 */
void Player::back()
{
    switchOrPause(backIndex());
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
    Audio *audio = currentAudio();
    if (!audio)
        return;

    total = total / 1000;
    if (total <= audio->length())
        emit positionChanged(total);
    else
        next();
}

/*
 * Initializes bass.
 *
 * :return: success
 */
bool Player::bassCreate()
{
    if (!BASS_Init(-1, 44100, 0, 0, NULL))
    {
        log("Player: Cannot initialize BASS");
        return false;
    }
    return true;
}

/*
 * Frees bass.
 *
 * :return: success
 */
bool Player::bassFree()
{
    if (!BASS_Free())
    {
        log("Player: Cannot free BASS");
        return false;
    }
    return true;
}

/*
 * Creates a bass stream from an audio pointer.
 * If the stream is currently occupied it gets
 * freed before reassigning.
 *
 * :param audio: audio pointer
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
        log("Player: Cannot free stream");
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
 * Sets the volume of the current channel.
 * The volume gets divided to get the float
 * value bass needs. The quotient is 1000
 * which seems to be a reasonable value.
 *
 * :return: success
 */
bool Player::bassSetVolume(int volume)
{
    if (!bassValidStream())
            return false;

    if (!BASS_ChannelSetAttribute(m_stream, BASS_ATTRIB_VOL, (float) volume / 1000))
    {
        log("Player: Cannot set volume");
        return false;
    }
    return true;
}

/*
 * Sets position of bass channel.
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
        log("Player: Cannot set position");
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
    if (!bassValidStream()
            || BASS_ChannelIsActive(m_stream) == BASS_ACTIVE_PLAYING)
        return false;

    if (!BASS_ChannelPlay(m_stream, false))
    {
        log("Player: Cannot play stream");
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
    if (!bassValidStream()
            || BASS_ChannelIsActive(m_stream) == BASS_ACTIVE_STOPPED
            || BASS_ChannelIsActive(m_stream) == BASS_ACTIVE_PAUSED)
        return false;

    if (!BASS_ChannelPause(m_stream))
    {
        log("Player: Cannot pause stream");
        return false;
    }
    return true;
}

/*
 * Small function for logging purposes. If
 * there is a current audio pointer it gets
 * added to the message.
 *
 * :param message: message
 */
void Player::log(const QString &message)
{
    QString log = message;
    Audio *audio = currentAudio();
    if (audio)
        log.append(QString(" '%1'").arg(audio->path()));
    Logger::log(log);
}

/*
 * Checks if the index is valid.
 *
 * :return: valid
 */
bool Player::validIndex(int index)
{
    return !(index < 0 || index >= m_playlist.size());
}

/*
 * Smoothly switches to an index and pauses
 * if the index is invalid.
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
 * Returns -1 if there is no next index.
 *
 * :return: index
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
 * Returns -1 if there is no previous index.
 *
 * :return: index
 */
int Player::backIndex()
{
    if (!validIndex(m_index))
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
    Audio *audio = currentAudio();
    if (!audio)
        return;

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
}

/*
 * Unshuffles current playlist and
 * sets index to current audio.
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
 * Sets active audio. The current stream get freed and a
 * new one get created. The volume for the stream gets set
 * and the timer gets restarded. If the player is in the
 * playing state it player, otherwise it pauses.
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
