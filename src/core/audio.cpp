#include "audio.hpp"

#include <QDateTime>
#include <QFileInfo>

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

Tag &Audio::tag()
{
    return m_tag;
}

Tag &Audio::tag() const
{
    return const_cast<Tag &>(static_cast<const Audio &>(*this).tag());
}

Cover &Audio::cover()
{
    return m_cover;
}

Cover &Audio::cover() const
{
    return const_cast<Cover &>(static_cast<const Audio &>(*this).cover());
}

Duration &Audio::duration()
{
    return m_duration;
}

Duration &Audio::duration() const
{
    return const_cast<Duration &>(static_cast<const Audio &>(*this).duration());
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
