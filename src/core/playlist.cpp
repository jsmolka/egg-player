#include "playlist.hpp"

Playlist::Playlist(QObject *parent)
    : QObject(parent)
    , m_index(-1)
    , m_loop(false)
    , m_shuffle(false)
{

}

Playlist::~Playlist()
{

}

void Playlist::setIndex(int index)
{
    m_index = index;
}

int Playlist::index() const
{
    return m_index;
}

void Playlist::setLoop(bool loop)
{
    m_loop = loop;
    cfgPlayer->setLoop(loop);
}

bool Playlist::isLoop() const
{
    return m_loop;
}

void Playlist::setShuffle(bool shuffle)
{
    m_shuffle = shuffle;
    cfgPlayer->setShuffle(shuffle);

    if (shuffle)
        this->shuffle();
    else
        this->unshuffle();
}

bool Playlist::isShuffle() const
{
    return m_shuffle;
}

void Playlist::changeIndex(int index)
{
    if (isValidIndex(index))
        setIndex(index);

    emit indexChanged(index);
}

Audio * Playlist::audioAt(int index)
{
    return isValidIndex(index) ? m_audios->at(m_indices.at(index)) : nullptr;
}

Audio * Playlist::currentAudio()
{
    return audioAt(m_index);
}

void Playlist::create(Audios *audios)
{
    m_audios = audios;

    m_indices.clear();
    for (int i = 0; i < m_audios->size(); ++i)
        m_indices << i;

    setShuffle(m_shuffle);
}

void Playlist::next()
{
    changeIndex(nextIndex());
}

void Playlist::previous()
{
    changeIndex(previousIndex());
}

void Playlist::onAudiosRemoved(int index)
{
    for (auto iter = m_indices.begin(); iter != m_indices.end(); ++iter)
    {
        if (*iter == index)
            iter = m_indices.erase(iter);

        if (*iter > index)
            --*iter;
    }
}

bool Playlist::isValidIndex(int index)
{
    return index >= 0 && index < m_indices.size();
}

int Playlist::nextIndex()
{
    if (!isValidIndex(m_index))
        return -1;

    if (m_index == m_indices.size() - 1)
        return m_loop ? 0 : -1;

    return ++m_index;
}

int Playlist::previousIndex()
{
    if (!isValidIndex(m_index))
        return -1;

    if (m_index == 0)
        return m_loop ? m_indices.size() - 1 : -1;

    return --m_index;
}

void Playlist::shuffle()
{
    int index = m_index;
    std::random_shuffle(m_indices.begin(), m_indices.end());
    std::swap(m_indices[0], m_indices[m_indices.indexOf(index)]);
    m_index = 0;
}

void Playlist::unshuffle()
{
    int index = m_indices.at(m_index);
    std::sort(m_indices.begin(), m_indices.end(), std::less<int>());
    m_index = m_indices.indexOf(index);

}
