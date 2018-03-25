#include "library.hpp"

Library::Library()
{

}

Library::Library(const QString &path)
{
    loadFiles(path);
}

Library::Library(QStringList paths)
{
    for (QString path : paths)
        loadFiles(path);
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
    for (Audio audio : m_audioList)
        if (QString::compare(audio.title(), title, cs))
            result << audio;
    return result;
}

AudioList Library::getByArtist(const QString &artist, Qt::CaseSensitivity cs)
{
    AudioList result;
    for (Audio audio : m_audioList)
        if (QString::compare(audio.artist(), artist, cs))
            result << audio;
    return result;
}

AudioList Library::getByAlbum(const QString &album, Qt::CaseSensitivity cs)
{
    AudioList result;
    for (Audio audio : m_audioList)
        if (QString::compare(audio.album(), album, cs))
            result << audio;
    return result;
}

AudioList Library::searchByTitle(const QString &title, Qt::CaseSensitivity cs)
{
    AudioList result;
    for (Audio audio : m_audioList)
        if (audio.title().contains(title, cs))
            result << audio;
    return result;
}

AudioList Library::searchByArtist(const QString &artist, Qt::CaseSensitivity cs)
{
    AudioList result;
    for (Audio audio : m_audioList)
        if (audio.artist().contains(artist, cs))
            result << audio;
    return result;
}

AudioList Library::searchByAlbum(const QString &album, Qt::CaseSensitivity cs)
{
    AudioList result;
    for (Audio audio : m_audioList)
        if (audio.album().contains(album, cs))
            result << audio;
    return result;
}

void Library::sortByTitle(bool reverse)
{
    m_audioList.sortByTitle(reverse);

    emit libraryUpdated();
}

void Library::sortByArtist(bool reverse)
{
    m_audioList.sortByArtist(reverse);

    emit libraryUpdated();
}

void Library::sortByAlbum(bool reverse)
{
    m_audioList.sortByAlbum(reverse);

    emit libraryUpdated();
}

Audio * Library::at(quint32 idx)
{
    return &m_audioList[idx];
}

void Library::libraryUpdated()
{

}

void Library::loadFiles(const QString &path)
{
    QStringList filePaths = FileUtil::glob(path, "*.mp3");
    if (!filePaths.isEmpty())
    {
        for (QString filePath : filePaths)
        {
            Audio audio(filePath);
            if (audio.isValid())
                m_audioList << audio;
        }
    }
}
