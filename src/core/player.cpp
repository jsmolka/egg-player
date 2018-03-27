#include "player.hpp"

Player::Player(QWidget *parent) : QWidget(parent)
{
    qsrand(time(0));

    pm_player = new QMediaPlayer;
    pm_player->setPlaylist(new QMediaPlaylist);
    m_loop = false;
    m_shuffled = false;
    m_playing = false;
    m_currentIndex = -1;

    connect(pm_player->playlist(), SIGNAL(currentIndexChanged(int)), this, SLOT(autoPlay(int)));
    connect(pm_player->playlist(), SIGNAL(currentIndexChanged(int)), this, SLOT(audioChanged()));
}

void Player::setCurrentIndex(int index)
{
    m_currentIndex = index;
    if (index != -1)
        insertAudio(index);
}

int Player::currentIndex()
{
    return m_currentIndex;
}

void Player::setLoop(bool loop)
{
    m_loop = loop;
}

bool Player::isLoop() const
{
    return m_loop;
}

void Player::setShuffled(bool shuffle)
{
    m_shuffled = shuffle;
}

bool Player::isShuffled() const
{
    return m_shuffled;
}

int Player::volume()
{
    return pm_player->volume();
}

int Player::position()
{
    return pm_player->position();
}

bool Player::isPlaying() const
{
    return m_playing;
}

void Player::setAudioList(AudioList audioList)
{
    m_playlist.clear();

    for (int i = 0; i < audioList.size(); i++)
        m_playlist << AudioPosition(i, audioList[i]);

    m_shuffled = false;
}

Audio Player::audioAt(int index)
{
    return m_playlist[index].audio;
}

Audio Player::currentAudio()
{
    return audioAt(m_currentIndex);
}

int Player::nextIndex()
{
    if (m_currentIndex == -1)
        return -1;
    if (m_currentIndex == m_playlist.size() - 1)
    {
        if (m_loop)
            return 0;
        else
            return -1;
    }
    return ++m_currentIndex;
}

int Player::backIndex()
{
    if (m_currentIndex == -1)
        return -1;
    if (m_currentIndex == 0)
    {
        if (m_loop)
            return m_playlist.size() - 1;
        else
            return -1;
    }
    return --m_currentIndex;
}

void Player::shuffle()
{
    Audio audio = currentAudio();

    std::random_shuffle(m_playlist.begin(), m_playlist.end());

    for (int i = 0; i < m_playlist.size(); i++)
    {
        if (audio == audioAt(i))
        {
            m_playlist.swap(0, i);
            break;
        }
    }
    m_currentIndex = 0;
    m_shuffled = true;
}

void Player::unshuffle()
{
    Audio audio = currentAudio();

    std::sort(m_playlist.begin(), m_playlist.end(),
        [](const AudioPosition &ap1, const AudioPosition &ap2) {return ap1.index < ap2.index;});

    for (int i = 0; i < m_playlist.size(); i++)
    {
        if (audio == audioAt(i))
        {
            m_currentIndex = i;
            break;
        }
    }
    m_shuffled = false;
}

void Player::setVolume(int volume)
{
    pm_player->setVolume(volume);
}

void Player::setPosition(int position)
{
    pm_player->setPosition(position);
}

void Player::play()
{
    pm_player->play();
    m_playing = true;
}

void Player::pause()
{
    pm_player->pause();
    m_playing = false;
}

void Player::next()
{
    int index = nextIndex();
    if (index != -1)
        setCurrentIndex(index);
    else
        emit stopped();
}

void Player::back()
{
    int index = backIndex();
    if (index != -1)
        setCurrentIndex(index);
}

void Player::autoPlay(int index)
{
    if (index != 0)
        next();
}

void Player::audioChanged()
{
    int index = currentIndex();
    if (index != -1)
        emit changed();
}

void Player::insertAudio(int index)
{
    QMediaPlaylist *playlist = pm_player->playlist();

    playlist->clear();
    playlist->addMedia(audioAt(index).url());
    playlist->setCurrentIndex(0);

    if (m_playing)
        play();
}

