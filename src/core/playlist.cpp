#include "playlist.hpp"

#include "config.hpp"

Playlist::Playlist(QObject *parent)
    : QObject(parent)
    , m_audios(nullptr)
    , m_indices()
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
    cfgPlayer.setLoop(loop);
}

bool Playlist::isLoop() const
{
    return m_loop;
}

void Playlist::setShuffle(bool shuffle)
{
    m_shuffle = shuffle;
    cfgPlayer.setShuffle(shuffle);

    if (m_indices.isEmpty())
        return;

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
    return isValidIndex(index)
        ? m_audios->at(m_indices.at(index))
        : nullptr;
}

Audio * Playlist::currentAudio()
{
    return audioAt(m_index);
}

void Playlist::create(Audios *audios)
{
    createAudios(audios);
    createIndices(audios->size());

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

void Playlist::onAudiosInserted(int index)
{
    Q_UNUSED(index);

    m_indices << m_indices.size();
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

    if (m_index >= index)
        --m_index;
}

void Playlist::createAudios(Audios *audios)
{
    if (m_audios)
    {
        disconnect(m_audios, &Audios::inserted, this, &Playlist::onAudiosInserted);
        disconnect(m_audios, &Audios::removed, this, &Playlist::onAudiosRemoved);
    }

    m_audios = audios;

    connect(m_audios, &Audios::inserted, this, &Playlist::onAudiosInserted);
    connect(m_audios, &Audios::removed, this, &Playlist::onAudiosRemoved);
}

void Playlist::createIndices(int size)
{
    m_indices = QVector<int>(size);
    std::iota(m_indices.begin(), m_indices.end(), 0);
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
    const int old = m_index;
    std::random_shuffle(m_indices.begin(), m_indices.end());
    const int current = m_indices.indexOf(old);
    std::swap(m_indices[0], m_indices[current]);
    m_index = 0;
}

void Playlist::unshuffle()
{
    const int current = m_indices.at(m_index);
    createIndices(m_indices.size());
    m_index = current;
}
