#include "audio.hpp"

#include <QDateTime>
#include <QFileInfo>

#include "core/logger.hpp"

Audio::Audio(QObject *parent)
    : QObject(parent)
    , m_valid(false)
    , m_cached(false)
    , m_outdated(false)
    , m_modified(0)
{

}

Audio::Audio(const QString &file, QObject *parent)
    : Audio(parent)
{
    setFile(file);

    update();
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

bool Audio::update()
{
    m_valid = m_tag.read();
    m_duration.setSecs(m_tag.duration());

    const QDateTime modified = QFileInfo(m_file).lastModified();
    if (modified.isNull() || !modified.isValid())
    {
        EGG_LOG("Cannot get last modification time %1", m_file);
        return false;
    }
    m_modified = modified.toSecsSinceEpoch();

    return m_valid;
}
