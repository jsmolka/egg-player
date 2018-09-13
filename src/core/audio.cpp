#include "audio.hpp"

#include "logger.hpp"
#include "tag.hpp"
#include "utils.hpp"

Audio::Audio(QObject *parent)
    : QObject(parent)
    , m_valid(false)
    , m_cached(false)
    , m_outdated(false)
    , m_modified(0)
{

}

Audio::Audio(const File &file, QObject *parent)
    : Audio(parent)
{
    setFile(file);

    update();

    connect(&m_tag, &Tag::updated, this, &Audio::onTagUpdated);
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

void Audio::setModified(qint64 modified)
{
    m_modified = modified;
}

qint64 Audio::modified() const
{
    return m_modified;
}

Tag &Audio::tag()
{
    return m_tag;
}

Cover &Audio::cover()
{
    return m_cover;
}

void Audio::update()
{
    m_tag.blockSignals(true);

    m_valid = m_tag.readTag();
    m_modified = QFileInfo(m_file).lastModified().toSecsSinceEpoch();
    emit updated(this);

    m_tag.blockSignals(false);
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
