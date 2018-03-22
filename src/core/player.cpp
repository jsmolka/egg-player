#include "player.hpp"

Player::Player(QObject *parent) : QMediaPlayer(parent)
{
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

bool Player::refresh()
{
    if (!m_playlist->clear())
        return false;

    for (Audio audioFile : m_audioList)
        m_playlist->addMedia(audioFile.url());

    return true;
}
