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
    m_file = file;
    m_tag.setFile(file);
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
    return const_cast<Tag &>(m_tag);
}

Cover &Audio::cover()
{
    return m_cover;
}

Cover &Audio::cover() const
{
    return const_cast<Cover &>(m_cover);
}

Duration &Audio::duration()
{
    return m_duration;
}

Duration &Audio::duration() const
{
    return const_cast<Duration &>(m_duration);
}

bool Audio::update()
{
    m_valid = m_tag.read();
    m_duration.setSecs(m_tag.duration());
    m_modified = QFileInfo(m_file).lastModified().toSecsSinceEpoch();

    return m_valid;
}
