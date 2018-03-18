#include "audiofile.hpp"

AudioFile::AudioFile(QString path)
{
    m_path = path;
    m_ref = TagLib::FileRef(path.toLatin1().data());

    if (!m_ref.isNull())
    {
        m_isValid = readTags() && readAudio();
    }
    else
    {
        m_isValid = false;
    }

    if (!readImage())
    {
        m_image = QImage(IMG_DEFAULT_COVER);
    }
}

bool AudioFile::isValid() const
{
    return m_isValid;
}

QString AudioFile::path() const
{
    return m_path;
}

QString AudioFile::title() const
{
    return m_title;
}

QString AudioFile::artist() const
{
    return m_artist;
}

QString AudioFile::album() const
{
    return m_album;
}

QString AudioFile::genre() const
{
    return m_genre;
}

quint32 AudioFile::year() const
{
    return m_year;
}

quint32 AudioFile::track() const
{
    return m_track;
}

quint32 AudioFile::length() const
{
    return m_length;
}

quint32 AudioFile::bitrate() const
{
    return m_bitrate;
}

quint32 AudioFile::seconds() const
{
    return m_length % 60;
}

quint32 AudioFile::minutes() const
{
    return (m_length - seconds()) / 60;
}

QImage AudioFile::image() const
{
    return m_image;
}

bool AudioFile::readTags()
{
    if (!m_ref.tag())
    {
        return false;
    }

    TagLib::Tag *tag = m_ref.tag();

    m_title = QString(tag->title().toCString());
    m_artist = QString(tag->artist().toCString());
    m_album = QString(tag->album().toCString());
    m_genre = QString(tag->genre().toCString());
    m_year = tag->year();
    m_track = tag->track();

    return true;
}

bool AudioFile::readAudio()
{
    if (!m_ref.audioProperties())
    {
        return false;
    }

    TagLib::AudioProperties *audio = m_ref.audioProperties();

    m_length = audio->length();
    m_bitrate = audio->bitrate();

    return true;
}

bool AudioFile::readImage()
{
    /*
     * TODO:
     * implement
     * ini setting to auto load cover.png
     * support for other file types
     */
    return false;
}
