#include "audio.hpp"

Audio::Audio(const QString &path)
    : m_path(path)
    , m_cached(false)
    , m_outdated(false)
    , m_cover(0)
{
    update();
}

Audio::Audio(const QString &path,
             const QString &title,
             const QString &artist,
             const QString &album,
             const QString &genre,
             int year,
             int track,
             int length,
             int coverId,
             qint64 modified)
    : m_valid(true)
    , m_cached(true)
    , m_path(path)
    , m_title(title)
    , m_artist(artist)
    , m_album(album)
    , m_genre(genre)
    , m_year(year)
    , m_track(track)
    , m_duration(length)
    , m_cover(coverId)
    , m_modified(modified)
{
    m_outdated = modified != FileUtil::modified(path);
}

Audio::~Audio()
{

}

void Audio::setValid(bool valid)
{
    m_valid = valid;
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

void Audio::setOutdated(bool outdated)
{
    m_outdated = outdated;
}

bool Audio::isOutdated() const
{
    return m_outdated;
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

qint64 Audio::modified() const
{
    return m_modified;
}

void Audio::update()
{
    if (!(m_valid = readTags()))
    {
        if (!FileUtil::exists(m_path))
            log("Audio: File does not exist %1", {m_path});
        else
            log("Audio: Cannot read tags %1", {m_path});
    }
    m_modified = FileUtil::modified(m_path);
}

const wchar_t * Audio::widePath() const
{
    return reinterpret_cast<const wchar_t *>(m_path.constData());
}

bool Audio::operator<(const Audio &other) const
{
    return title().compare(other.title(), Qt::CaseInsensitive) < 0;
}

bool Audio::operator>(const Audio &other) const
{
    return other < *this;
}

bool Audio::operator<=(const Audio &other) const
{
    return !(*this > other);
}

bool Audio::operator>=(const Audio &other) const
{
    return !(*this < other);
}

bool Audio::operator==(const Audio &other) const
{
    return path() == other.path();
}

bool Audio::operator!=(const Audio &other) const
{
    return !(*this == other);
}

bool Audio::readTags()
{
    Tag tag(widePath());

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
