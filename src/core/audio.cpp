#include "audio.hpp"

#include <QDateTime>
#include <QFileInfo>

#include "core/logger.hpp"

Audio::Audio()
    : m_valid(false)
    , m_cached(false)
    , m_outdated(false)
    , m_modified(0)
{

}

Audio::Audio(const QString &file)
    : Audio()
{
    setFile(file);

    read();
}

Audio *Audio::readFromFile(const QString &file)
{
    Audio *audio = new Audio(file);
    if (audio->isValid())
        return audio;

    delete audio;
    return nullptr;
}

void Audio::setFile(const QString &file)
{
    m_tag.setFile(file);

    m_file = file;
}

QString Audio::file() const
{
    return m_file;
}

const Tag &Audio::tag() const
{
    return m_tag;
}

const Cover &Audio::cover() const
{
    return m_cover;
}

const Duration &Audio::duration() const
{
    return m_duration;
}

Tag &Audio::tag()
{
    return EGG_REF_CAST(Audio, Tag, tag);
}

Cover &Audio::cover()
{
    return EGG_REF_CAST(Audio, Cover, cover);
}

Duration &Audio::duration()
{
    return EGG_REF_CAST(Audio, Duration, duration);
}

bool Audio::read()
{
    const QFileInfo info(m_file);

    if (!info.exists())
    {
        EGG_LOG("Cannot read non existing file %1", m_file);
        return false;
    }

    m_valid = m_tag.read();
    m_duration.setSecs(m_tag.duration());

    const QDateTime modified = info.lastModified();
    if (modified.isNull() || !modified.isValid())
    {
        EGG_LOG("Cannot get last modification time %1", m_file);
        return false;
    }
    m_modified = modified.toSecsSinceEpoch();

    return m_valid;
}
