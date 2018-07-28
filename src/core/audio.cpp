#include "audio.hpp"

Audio::Audio(const QString &path)
    : m_path(path)
    , m_cover(-1)
    , m_cached(false)
{
    if (!(m_valid = readTags()))
    {
        if (!FileUtil::exists(path))
            log("Audio: File does not exist %1", {m_path});
        else
            log("Audio: Cannot read tags %1", {m_path});
    }
}

Audio::Audio(const QString &path,
             const QString &title,
             const QString &artist,
             const QString &album,
             const QString &genre,
             int year,
             int track,
             int length,
             int coverId)
    : m_valid(true)
    , m_path(path)
    , m_title(title)
    , m_artist(artist)
    , m_album(album)
    , m_genre(genre)
    , m_year(year)
    , m_track(track)
    , m_duration(length)
    , m_cover(coverId)
    , m_cached(true)
{

}

Audio::~Audio()
{

}

bool Audio::isValid() const
{
    return m_valid;
}

void Audio::setCached(bool cached)
{
    m_cached = cached;
}

bool Audio::isCached() const
{
    return m_cached;
}

QString Audio::path() const
{
    return m_path;
}

QString Audio::title() const
{
    return m_title;
}

QString Audio::artist() const
{
    return m_artist;
}

QString Audio::album() const
{
    return m_album;
}

QString Audio::genre() const
{
    return m_genre;
}

int Audio::year() const
{
    return m_year;
}

int Audio::track() const
{
    return m_track;
}

Duration * Audio::duration()
{
    return &m_duration;
}

Cover * Audio::cover()
{
    return &m_cover;
}

const wchar_t * Audio::pathWChar() const
{
    return reinterpret_cast<const wchar_t *>(m_path.constData());
}

bool Audio::readTags()
{
    Tag tag(pathWChar());

    if (!tag.isValid() || !tag.isAudioValid())
        return false;

    m_duration = Duration(tag.duration());

    if (tag.isTagValid())
    {
        m_title = tag.title();
        m_artist = tag.artist();
        m_album = tag.album();
        m_genre = tag.genre();
        m_year = tag.year();
        m_track = tag.track();
    }

    if (m_title.isEmpty())
        m_title = FileUtil::fileName(m_path);

    return true;
}
