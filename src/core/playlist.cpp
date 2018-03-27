#include "playlist.hpp"

Playlist::Playlist()
{
    m_shuffled = false;
}

Playlist::Playlist(const AudioList &audioList)
{
    setAudioList(audioList);
}

void Playlist::setAudioList(const AudioList &audioList)
{
    m_itemList.clear();
    for (int i = 0; i < audioList.size(); i++)
    {
        Item item(i, (Audio *)&audioList[i]);
        m_itemList << item;
    }
    m_shuffled = false;
}

bool Playlist::isShuffled() const
{
    return m_shuffled;
}

int Playlist::size() const
{
    return m_itemList.size();
}

QList<Playlist::Item> * Playlist::itemList()
{
    return &m_itemList;
}

void Playlist::sort()
{
    std::sort(m_itemList.begin(), m_itemList.end(),
        [](const Item &i1, const Item &i2) {return i1.index < i2.index;});
    m_shuffled = false;
}

void Playlist::shuffle(int index)
{
    int size = m_itemList.size();
    for (int i = size - 1; i > 0; i--)
    {
        int j = RandUtil::randint(i + 1);
        if (i == index)
            index = j;
        else if (j == index)
            index = i;
        m_itemList.swap(i, j);
    }

    if (index != 0)
        m_itemList.swap(0, index);
    m_shuffled = true;
}

Audio * Playlist::audioAt(int index)
{
    return m_itemList[index].audio;
}
