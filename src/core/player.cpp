#include "player.hpp"

Player::Player(QObject *parent) : QMediaPlayer(parent)
{
    qsrand(time(0));

    pm_playlist = new QMediaPlaylist;
    setPlaylist(pm_playlist);
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
    return pm_playlist;
}

void Player::setIndex(quint32 index)
{
    pm_playlist->setCurrentIndex(index);
}

quint32 Player::index() const
{
    return pm_playlist->currentIndex();
}

Audio Player::currentAudio()
{
    return m_audioList.at(index());
}

void Player::setPlaybackMode(QMediaPlaylist::PlaybackMode mode)
{
    pm_playlist->setPlaybackMode(mode);
}

bool Player::refresh()
{
    if (!pm_playlist->clear())
        return false;

    for (Audio audio : m_audioList)
        pm_playlist->addMedia(audio.url());

    return true;
}

void Player::shuffle()
{
    std::random_shuffle(m_audioList.begin(), m_audioList.end());

    refresh();
}
