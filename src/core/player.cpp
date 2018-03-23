#include "player.hpp"

Player::Player(QObject *parent) : QMediaPlayer(parent)
{
    qsrand(time(0));

    m_playlist = new QMediaPlaylist;
    setPlaylist(m_playlist);
}

void Player::setAudioList(AudioList audioList)
{
    m_audioList = audioList;

    refresh();
}

AudioList Player::audioList() const
{
    return m_audioList;
}

QMediaPlaylist * Player::playlist() const
{
    return m_playlist;
}

void Player::setIndex(quint32 index)
{
    m_playlist->setCurrentIndex(index);
}

quint32 Player::index() const
{
    return m_playlist->currentIndex();
}

Audio Player::audio() const
{
    return m_audioList.at(index());
}

void Player::setPlaybackMode(QMediaPlaylist::PlaybackMode mode)
{
    m_playlist->setPlaybackMode(mode);
}

bool Player::refresh()
{
    if (!m_playlist->clear())
        return false;

    for (Audio audio : m_audioList)
        m_playlist->addMedia(audio.url());

    return true;
}

void Player::shuffle()
{
    std::random_shuffle(m_audioList.begin(), m_audioList.end());

    refresh();
}
