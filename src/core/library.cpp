#include "library.hpp"

Library::Library(const QString &path)
{
    loadFiles(path);
}

Library::Library(QStringList pathList)
{
    for (QString path : pathList)
        loadFiles(path);
}

QList<AudioFile> Library::library() const
{
    return m_library;
}

bool Library::isEmpty() const
{
    return m_library.isEmpty();
}

QList<AudioFile> Library::getByTitle(const QString &title, Qt::CaseSensitivity cs)
{
    QList<AudioFile> result;
    for (AudioFile audioFile : m_library)
        if (QString::compare(audioFile.title(), title, cs))
            result << audioFile;
    return result;
}

QList<AudioFile> Library::getByArtist(const QString &artist, Qt::CaseSensitivity cs)
{
    QList<AudioFile> result;
    for (AudioFile audioFile : m_library)
        if (QString::compare(audioFile.artist(), artist, cs))
            result << audioFile;
    return result;
}

QList<AudioFile> Library::getByAlbum(const QString &album, Qt::CaseSensitivity cs)
{
    QList<AudioFile> result;
    for (AudioFile audioFile : m_library)
        if (QString::compare(audioFile.album(), album, cs))
            result << audioFile;
    return result;
}

QList<AudioFile> Library::searchByTitle(const QString &title, Qt::CaseSensitivity cs)
{
    QList<AudioFile> result;
    for (AudioFile audioFile : m_library)
        if (audioFile.title().contains(title, cs))
            result << audioFile;
    return result;
}

QList<AudioFile> Library::searchByArtist(const QString &artist, Qt::CaseSensitivity cs)
{
    QList<AudioFile> result;
    for (AudioFile audioFile : m_library)
        if (audioFile.artist().contains(artist, cs))
            result << audioFile;
    return result;
}

QList<AudioFile> Library::searchByAlbum(const QString &album, Qt::CaseSensitivity cs)
{
    QList<AudioFile> result;
    for (AudioFile audioFile : m_library)
        if (audioFile.album().contains(album, cs))
            result << audioFile;
    return result;
}

void Library::sortByTitle()
{
    std::sort(m_library.begin(), m_library.end(),
              [](const AudioFile &af1, const AudioFile &af2) {return af1.title() < af2.title();});

    emit libraryUpdated();
}

void Library::sortByArtist()
{
    std::sort(m_library.begin(), m_library.end(),
              [](const AudioFile &af1, const AudioFile &af2) {return af1.artist() < af2.artist();});

    emit libraryUpdated();
}

void Library::sortByAlbum()
{
    std::sort(m_library.begin(), m_library.end(),
              [](const AudioFile &af1, const AudioFile &af2) {return af1.album() < af2.album();});

    emit libraryUpdated();
}

AudioFile Library::at(quint32 idx) const
{
    return m_library.at(idx);
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
            AudioFile audioFile(filePath);
            if (audioFile.isValid())
                m_library << audioFile;
        }
    }
}
