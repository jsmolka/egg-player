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
}

bool Playlist::isLoop() const
{
    return m_loop;
}

void Playlist::setShuffle(bool shuffle)
{
    m_shuffle = shuffle;

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
    if (validIndex(index))
        setIndex(index);

    emit indexChanged(index);
}

Audio * Playlist::audioAt(int index)
{
    return validIndex(index) ? m_items[index].audio : nullptr;
}

Audio * Playlist::currentAudio()
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

void Playlist::loadAudios(const Audios &audios)
{
    m_items.clear();
    m_items.reserve(audios.size());

    for (int i = 0; i < audios.size(); ++i)
        m_items << PlaylistItem(i, audios[i]);

    setShuffle(m_shuffle);
}

bool Playlist::validIndex(int index)
{
    return index >= 0 && index < m_items.size();
}

int Playlist::nextIndex()
{
    if (!validIndex(m_index))
        return -1;

    if (m_index == m_items.size() - 1)
        return m_loop ? 0 : -1;

    return ++m_index;
}

int Playlist::previousIndex()
{
    if (!validIndex(m_index))
        return -1;

    if (m_index == 0)
        return m_loop ? m_items.size() - 1 : -1;

    return --m_index;
}

int Playlist::indexOf(const Audio *audio)
{
    for (int i = 0; i < m_items.size(); ++i)
    {
        if (audio == m_items[i].audio)
            return i;
    }
    return 0;
}

void Playlist::shuffle()
{
    Audio *audio = currentAudio();

    std::random_shuffle(m_items.begin(), m_items.end());

    std::swap(m_items[0], m_items[indexOf(audio)]);
    m_index = 0;
}

void Playlist::unshuffle()
{
    Audio *audio = currentAudio();

    auto comparer = [](const PlaylistItem &i1, const PlaylistItem &i2) -> bool
    {
        return i1.index < i2.index;
    };

    std::sort(m_items.begin(), m_items.end(), comparer);
    m_index = indexOf(audio);
}
