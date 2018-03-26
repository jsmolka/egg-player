#include "player.hpp"

Player::Player(QObject *parent) : QMediaPlayer(parent)
{
    qsrand(time(0));

    pm_playlist = new QMediaPlaylist;
    setPlaylist(pm_playlist);
}

void Player::setAudioList(const AudioList &audioList)
{
    m_audioList = audioList;

    refresh();
}

AudioList Player::audioList() const
{
    return m_audioList;
}

void Player::setCurrentIndex(int index)
{
    if (0 <= index && index << m_audioList.size())
        pm_playlist->setCurrentIndex(index);
    else
        pm_playlist->setCurrentIndex(0);
}

int Player::currentIndex() const
{
    int index = pm_playlist->currentIndex();
    if (0 <= index && index < m_audioList.size())
        return index;
    else
        return -1;
}

Audio * Player::currentAudio()
{
    int index = currentIndex();
    if (index != -1)
        return &m_audioList[index];
    else
        return 0;
}

QString Player::currentTitle()
{
    Audio *audio = currentAudio();
    if (audio)
        return currentAudio()->title();
    else
        return QString();
}

QString Player::currentArtist()
{
    Audio *audio = currentAudio();
    if (audio)
        return currentAudio()->artist();
    else
        return QString();
}

QPixmap Player::currentCover()
{
    Audio *audio = currentAudio();
    if (audio)
        return currentAudio()->pixmap(50);
    else
        return QPixmap();
}

QString Player::titleAt(int index)
{
    return m_audioList[index].title();
}

QString Player::artistAt(int index)
{
    return m_audioList[index].artist();
}

QPixmap Player::coverAt(int index)
{
    return m_audioList[index].pixmap(50);
}

void Player::setLoop(bool loop)
{
    if (loop)
        pm_playlist->setPlaybackMode(QMediaPlaylist::PlaybackMode::Loop);
    else
        pm_playlist->setPlaybackMode(QMediaPlaylist::PlaybackMode::Sequential);
}

bool Player::isLoop()
{
    return pm_playlist->playbackMode() == QMediaPlaylist::PlaybackMode::Loop;
}

int Player::nextIndex()
{
    int index = currentIndex();
    if (index == -1)
        return -1;
    if (index == m_audioList.size() - 1)
    {
        if (isLoop())
            return 0;
        else
            return -1;
    }
    return ++index;
}

int Player::backIndex()
{
    int index = currentIndex();
    if (index == -1)
        return -1;
    if (index == 0)
    {
        if (isLoop())
            return m_audioList.size() - 1;
        else
            return -1;
    }
    return --index;
}

void Player::refresh()
{
    pm_playlist->clear();

    for (Audio audio : m_audioList)
        pm_playlist->addMedia(audio.url());
}

void Player::shuffle()
{
    std::random_shuffle(m_audioList.begin(), m_audioList.end());

    refresh();
}
