#include "audio.hpp"

#include <QTime>

#include "logger.hpp"
#include "tag.hpp"

Audio::Audio(QObject *parent)
    : QObject(parent)
    , m_valid(false)
    , m_cached(false)
    , m_outdated(false)
    , m_modified(0)
{
    m_tag.setYear(0);
    m_tag.setTrack(0);
}

Audio::Audio(const QString &path, QObject *parent)
    : Audio(parent)
{
    m_file = path;
    m_tag.setFile(path);

    update();

    connect(&m_tag, &Tag::updated, this, &Audio::onTagUpdated);
}

Audio::Audio(const QString &path,
             const QString &title,
             const QString &artist,
             const QString &album,
             const QString &genre,
             int year,
             int track,
             int duration,
             int coverId,
             qint64 modified,
             QObject *parent)
    : QObject(parent)
    , m_valid(true)
    , m_cached(true)
    , m_file(path)
    , m_cover(coverId)
    , m_modified(modified)
{
    m_tag.setTitle(title);
    m_tag.setArtist(artist);
    m_tag.setAlbum(album);
    m_tag.setGenre(genre);
    m_tag.setYear(year);
    m_tag.setTrack(track);
    m_tag.setDuration(duration);

    m_outdated = modified != info().lastModified().toSecsSinceEpoch();
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

void Audio::setFile(const File &file)
{
    m_file = file;
    m_tag.setFile(file);
}

File Audio::file() const
{
    return m_file;
}

Tag &Audio::tag()
{
    return m_tag;
}

Cover &Audio::cover()
{
    return m_cover;
}

qint64 Audio::modified() const
{
    return m_modified;
}

QFileInfo Audio::info() const
{
    return QFileInfo(m_file);
}

void Audio::update()
{
    m_tag.blockSignals(true);
    if (!(m_valid = m_tag.readTag()))
    {
        if (QFileInfo::exists(m_file))
            LOG("Cannot read tags %1", m_file);
        else
            LOG("File does not exist %1", m_file);
    }
    m_modified = info().lastModified().toSecsSinceEpoch();

    emit updated(this);
    m_tag.blockSignals(false);
}

const wchar_t * Audio::wideFile() const
{
    return reinterpret_cast<const wchar_t *>(m_file.constData());
}

bool Audio::operator<(Audio &other) const
{
    return m_tag.title().compare(other.tag().title(), Qt::CaseInsensitive) < 0;
}

bool Audio::operator>(Audio &other) const
{
    return other.tag().title().compare(m_tag.title(), Qt::CaseInsensitive) < 0;
}

bool Audio::operator<=(Audio &other) const
{
    return !(*this > other);
}

bool Audio::operator>=(Audio &other) const
{
    return !(*this < other);
}

bool Audio::operator==(const QString &other) const
{
    return m_file == other;
}

bool Audio::operator==(Audio &other) const
{
    return *this == other.file();
}

bool Audio::operator!=(const QString &other) const
{
    return !(*this == other);
}

bool Audio::operator!=(Audio &other) const
{
    return !(*this == other);
}

void Audio::onTagUpdated()
{
    emit updated(this);
}
