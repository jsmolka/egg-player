#include "library.hpp"

Library::Library()
{

}

Library::Library(const QString &path)
{
    loadFiles(path);
}

Library::Library(const QStringList &paths)
{
    for (const QString &path : paths)
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
    for (const Audio &audio : m_audioList)
        if (QString::compare(audio.title(), title, cs))
            result << audio;
    return result;
}

AudioList Library::getByArtist(const QString &artist, Qt::CaseSensitivity cs)
{
    AudioList result;
    for (const Audio &audio : m_audioList)
        if (QString::compare(audio.artist(), artist, cs))
            result << audio;
    return result;
}

AudioList Library::getByAlbum(const QString &album, Qt::CaseSensitivity cs)
{
    AudioList result;
    for (const Audio &audio : m_audioList)
        if (QString::compare(audio.album(), album, cs))
            result << audio;
    return result;
}

AudioList Library::searchByTitle(const QString &title, Qt::CaseSensitivity cs)
{
    AudioList result;
    for (const Audio &audio : m_audioList)
        if (audio.title().contains(title, cs))
            result << audio;
    return result;
}

AudioList Library::searchByArtist(const QString &artist, Qt::CaseSensitivity cs)
{
    AudioList result;
    for (const Audio &audio : m_audioList)
        if (audio.artist().contains(artist, cs))
            result << audio;
    return result;
}

AudioList Library::searchByAlbum(const QString &album, Qt::CaseSensitivity cs)
{
    AudioList result;
    for (const Audio &audio : m_audioList)
        if (audio.album().contains(album, cs))
            result << audio;
    return result;
}

void Library::sortByTitle()
{
    m_audioList.sortByTitle();

    emit libraryUpdated();
}

void Library::sortByArtist()
{
    m_audioList.sortByArtist();

    emit libraryUpdated();
}

void Library::sortByAlbum()
{
    m_audioList.sortByAlbum();

    emit libraryUpdated();
}

Audio * Library::at(int idx)
{
    return &m_audioList[idx];
}

void Library::libraryUpdated()
{

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
            Audio audio(file);
            if (audio.isValid())
            {
                QString artist = audio.artist();
                QString album = audio.album();

                if (!cache.exists(artist, album))
                    cache.insert(artist, album, audio.cover(200));

                m_audioList << audio;
            }
        }
    }
    cache.close();
}
