#include "playlist.hpp"

#include <algorithm>
#include <random>

Playlist::Playlist(QObject *parent)
    : QObject(parent)
    , m_state(nullptr)
    , m_index(-1)
    , m_loop(false)
    , m_shuffle(false)
{

}

bool Playlist::isLoop() const
{
    return m_loop;
}

bool Playlist::isShuffle() const
{
    return m_shuffle;
}

bool Playlist::isEmpty() const
{
    return m_indices.isEmpty();
}

int Playlist::index() const
{
    return m_index;
}

int Playlist::size() const
{
    return m_indices.size();
}

Audio *Playlist::audioAt(int index)
{
    return m_state->at(m_indices.at(index));
}

Audio *Playlist::currentAudio()
{
    return audioAt(m_index);
}

void Playlist::next()
{
    changeIndex(nextIndex());
}

void Playlist::previous()
{
    changeIndex(previousIndex());
}

void Playlist::loadFromState(audios::CurrentState *state, int index)
{
    m_index = index;

    setState(state);
    createIndices(state->size());

    setShuffle(m_shuffle);

    emit audioChanged(currentAudio());
}

void Playlist::setLoop(bool loop)
{
    m_loop = loop;
}

void Playlist::setShuffle(bool shuffle)
{
    m_shuffle = shuffle;

    if (size() <= 1)
        return;

    if (shuffle)
        this->shuffle();
    else
        this->unshuffle();
}

void Playlist::onStateRemoved(int index)
{
    auto iter = m_indices.begin();
    while (iter != m_indices.end())
    {
        if (*iter == index)
        {
            iter = m_indices.erase(iter);
        }
        else
        {
            if (*iter > index)
                (*iter)--;
            ++iter;
        }
    }

    if (m_index >= index)
        m_index--;
}

void Playlist::setState(audios::CurrentState *state)
{
    if (m_state)
    {
        disconnect(m_state, nullptr, this, nullptr);
        m_state->deleteLater();
    }
    m_state = state;

    connect(state, &audios::CurrentState::removed, this, &Playlist::onStateRemoved);
}

void Playlist::createIndices(int size)
{
    m_indices = Indices(size);
    std::iota(m_indices.begin(), m_indices.end(), 0);
}

void Playlist::changeIndex(int index)
{
    if (index != -1)
    {
        m_index = index;
        emit audioChanged(currentAudio());
    }
    else
    {
        emit endReached();
    }
}

int Playlist::nextIndex()
{
    if (m_index == size() - 1)
        return m_loop ? 0 : -1;

    return m_index + 1;
}

int Playlist::previousIndex()
{
    return (m_index == 0 && m_loop ? size() : m_index) - 1;
}

void Playlist::shuffle()
{
    std::random_shuffle(m_indices.begin(), m_indices.end());
    std::swap(m_indices[0], m_indices[m_indices.indexOf(m_index)]);
    m_index = 0;
}

void Playlist::unshuffle()
{
    m_index = m_indices.at(m_index);
    createIndices(m_indices.size());
}
