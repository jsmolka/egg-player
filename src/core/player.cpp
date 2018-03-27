#include "player.hpp"

#include <QDebug>

Player::Player(QObject *parent) : QMediaPlayer(parent)
{
    pm_playlist = new QMediaPlaylist;
    setPlaylist(pm_playlist);
    m_shuffled = false;
}

bool Player::isShuffled() const
{
    return m_shuffled;
}

void Player::setAudioList(const AudioList &audioList)
{
    m_playlist.setAudioList(audioList);

    pm_playlist->clear();

    for (int i = 0; i < m_playlist.size(); i++)
        pm_playlist->addMedia(m_playlist.audioAt(i)->url());

    m_shuffled = false;
}

void Player::setCurrentIndex(int index)
{
    if (0 <= index && index < m_playlist.size())
        pm_playlist->setCurrentIndex(index);
    else
        pm_playlist->setCurrentIndex(0);
}

int Player::currentIndex() const
{
    int index = pm_playlist->currentIndex();
    if (0 <= index && index < m_playlist.size())
        return index;
    else
        return -1;
}

void Player::setLoop(bool loop)
{
    if (loop)
        pm_playlist->setPlaybackMode(QMediaPlaylist::PlaybackMode::Loop);
    else
        pm_playlist->setPlaybackMode(QMediaPlaylist::PlaybackMode::Sequential);
}

bool Player::isLoop() const
{
    return pm_playlist->playbackMode() == QMediaPlaylist::PlaybackMode::Loop;
}

Audio * Player::currentAudio()
{
    int index = currentIndex();
    if (index != -1)
        return m_playlist.audioAt(index);
    else
        return 0;
}

int Player::nextIndex()
{
    int index = currentIndex();
    if (index == -1)
        return -1;
    if (index == m_playlist.size() - 1)
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
            return m_playlist.size() - 1;
        else
            return -1;
    }
    return --index;
}

void Player::shuffle()
{
    qDebug() << "Shuffeling";
    // Get current index in unshuffled list
    int index = currentIndex();
    if (index != -1 && !m_shuffled)
    {
        // Shuffle playlist so that index is first
        m_playlist.shuffle(index);

        for (int i = 0; i < m_playlist.size(); i++)
        {
            qDebug() << i << m_playlist.audioAt(i)->title();
        }
        // Remove all media objects apart from current
        if (index == 0)
        {
            // Remove media objects after current
            pm_playlist->removeMedia(1, m_playlist.size() - 1);
        }
        else
        {
            // Remove media objects around current
            pm_playlist->removeMedia(index + 1, m_playlist.size());
            pm_playlist->removeMedia(0, index - 1);
        }
        // Insert shuffled media objects after current
        pm_playlist->insertMedia(1, mediaContent(1, m_playlist.size()));
        m_shuffled = true;
    }
}

void Player::unshuffle()
{
    // Get current index in shuffled list
    int index = currentIndex();
    if (index != -1 && m_shuffled)
    {
        qDebug() << "Unshuffle with index" << index;
        // Get current audio
        Audio *audio = currentAudio();
        qDebug() << "Current audio" << audio->title();
        // Remove all media objects apart from current
        if (index == 0)
        {
            // Remove media objects after current
            pm_playlist->removeMedia(1, m_playlist.size() - 1);
        }
        else
        {
            // Remove media objects around current
            pm_playlist->removeMedia(index + 1, m_playlist.size());
            pm_playlist->removeMedia(0, index - 1);
        }
        // Go trough sorted list and find index of current audio
        int current;
        m_playlist.sort();
        for (int i = 0; i < m_playlist.size(); i++)
        {
            qDebug() << i << m_playlist.audioAt(i)->title();
        }
        for (int i = 0; i < m_playlist.size(); i++)
        {
            if (QString::compare(audio->path(), m_playlist.audioAt(i)->path())) // Compare pointers???
            {
                current = i;
                qDebug() << "Found index" << i;
                break;
            }
        }
        // Insert sorted media objects around current
        if (current == 0)
        {
            // Insert media objects after current
            pm_playlist->insertMedia(1, mediaContent(1, m_playlist.size()));
        }
        else
        {
            // Inser media objects around current
            pm_playlist->insertMedia(0, mediaContent(0, m_playlist.size() - current - 1));
            pm_playlist->insertMedia(current + 1, mediaContent(current + 1, m_playlist.size()));
        }
        m_shuffled = false;
    }

}

QList<QMediaContent> Player::mediaContent(int start, int end)
{
    QList<QMediaContent> result;
    for (int i = start; i < end; i++)
        result << QMediaContent(m_playlist.audioAt(i)->url());
    return result;
}
