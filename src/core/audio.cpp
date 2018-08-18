#include "audio.hpp"

Audio::Audio(QObject *parent)
    : QObject(parent)
    , m_valid(false)
{

}

Audio::Audio(const QString &path, QObject *parent)
    : QObject(parent)
    , m_path(path)
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
             qint64 modified,
             QObject *parent)
    : QObject(parent)
    , m_valid(true)
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
    m_outdated = modified != info().lastModified().toSecsSinceEpoch();
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

void Audio::setPath(const QString &path)
{
    m_path = path;
}

QString Audio::path() const
{
    return m_path;
}

void Audio::setTitle(const QString &title)
{
    m_title = title;

    emit updated(this);
}

QString Audio::title() const
{
    return m_title;
}

void Audio::setArtist(const QString &artist)
{
    m_artist = artist;

    emit updated(this);
}

QString Audio::artist() const
{
    return m_artist;
}

void Audio::setAlbum(const QString &album)
{
    m_album = album;

    emit updated(this);
}

QString Audio::album() const
{
    return m_album;
}

void Audio::setGenre(const QString &genre)
{
    m_genre = genre;

    emit updated(this);
}

QString Audio::genre() const
{
    return m_genre;
}

void Audio::setYear(int year)
{
    m_year = year;

    emit updated(this);
}

int Audio::year() const
{
    return m_year;
}

void Audio::setTrack(int track)
{
    m_track = track;

    emit updated(this);
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

QFileInfo Audio::info() const
{
    return QFileInfo(m_path);
}

void Audio::update()
{
    if (!(m_valid = readTags()))
    {
        if (!info().exists())
            LOG("File does not exist %1", m_path);
        else
            LOG("Cannot read tags %1", m_path);
    }
    m_modified = info().lastModified().toSecsSinceEpoch();

    emit updated(this);
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

bool Audio::operator==(const QString &other) const
{
    return path() == other;
}

bool Audio::operator==(const Audio &other) const
{
    return *this == other.path();
}

bool Audio::operator!=(const QString &other) const
{
    return !(*this == other);
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
        m_title = info().baseName();

    return true;
}
