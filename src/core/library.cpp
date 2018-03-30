#include "library.hpp"

Library::Library()
{

}

Library::Library(const QString &path)
{
    loadFiles(path);
}

Library::~Library()
{

}

AudioList Library::audioList() const
{
    return m_audioList;
}

bool Library::isEmpty() const
{
    return m_audioList.isEmpty();
}

AudioList Library::getByTitle(const QString &title, Qt::CaseSensitivity cs)
{
    AudioList result;
    for (Audio *audio : m_audioList)
        if (audio->title().compare(title, cs) == 0)
            result << audio;
    return result;
}

AudioList Library::getByArtist(const QString &artist, Qt::CaseSensitivity cs)
{
    AudioList result;
    for (Audio *audio : m_audioList)
        if (audio->artist().compare(artist, cs) == 0)
            result << audio;
    return result;
}

AudioList Library::getByAlbum(const QString &album, Qt::CaseSensitivity cs)
{
    AudioList result;
    for (Audio *audio : m_audioList)
        if (audio->album().compare(album, cs) == 0)
            result << audio;
    return result;
}

AudioList Library::searchByTitle(const QString &title, Qt::CaseSensitivity cs)
{
    AudioList result;
    for (Audio *audio : m_audioList)
        if (audio->title().contains(title, cs))
            result << audio;
    return result;
}

AudioList Library::searchByArtist(const QString &artist, Qt::CaseSensitivity cs)
{
    AudioList result;
    for (Audio *audio : m_audioList)
        if (audio->artist().contains(artist, cs))
            result << audio;
    return result;
}

AudioList Library::searchByAlbum(const QString &album, Qt::CaseSensitivity cs)
{
    AudioList result;
    for (Audio *audio : m_audioList)
        if (audio->album().contains(album, cs))
            result << audio;
    return result;
}

void Library::sortByTitle()
{
    m_audioList.sortByTitle();
}

void Library::sortByArtist()
{
    m_audioList.sortByArtist();
}

void Library::sortByAlbum()
{
    m_audioList.sortByAlbum();
}

Audio * Library::audioAt(int idx)
{
    return m_audioList[idx];
}

void Library::loadFiles(const QString &path)
{
    Cache cache;
    cache.connect();

    QStringList files = FileUtil::glob(path, "*.mp3");
    if (!files.isEmpty())
    {
        for (const QString &file : files)
        {
            Audio *audio = new Audio(file);
            if (audio->isValid())
            {
                if (!cache.exists(audio))
                    cache.insert(audio);

                m_audioList << audio;
            }
        }
    }
    cache.close();
}
