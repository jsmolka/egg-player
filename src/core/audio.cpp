#include "audio.hpp"

#include <QDateTime>
#include <QFileInfo>

#include "core/logger.hpp"

struct AudioPrivate
{
    QString file;
    bool valid = false;
    bool cached = false;
    bool outdated = false;
    qint64 modified = 0;
    Tag tag;
    Cover cover;
    Duration duration;
};

Audio::Audio()
    : d(new AudioPrivate)
{

}

Audio::Audio(const Audio &rhs)
    : d(rhs.d)
{

}

Audio::Audio(const QString &file)
    : Audio()
{
    setFile(file);

    read();
}

Audio &Audio::operator=(Audio rhs)
{
    swap(*this, rhs);

    return *this;
}

bool Audio::operator==(const Audio &rhs) const
{
    return d == rhs.d;
}

void Audio::setFile(const QString &file)
{
    d->tag.setFile(file);

    d->file = file;
}

QString Audio::file() const
{
    return d->file;
}

void Audio::setValid(bool valid)
{
    d->valid = valid;
}

bool Audio::isValid() const
{
    return d->valid;
}

void Audio::setCached(bool cached)
{
    d->cached = cached;
}

bool Audio::isCached() const
{
    return d->cached;
}

void Audio::setOutdated(bool outdated)
{
    d->outdated = outdated;
}

bool Audio::isOutdated() const
{
    return d->outdated;
}

void Audio::setModified(qint64 modified)
{
    d->modified = modified;
}

qint64 Audio::modified() const
{
    return d->modified;
}

const Tag &Audio::tag() const
{
    return d->tag;
}

const Cover &Audio::cover() const
{
    return d->cover;
}

const Duration &Audio::duration() const
{
    return d->duration;
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
    const QFileInfo info(d->file);

    if (!info.exists())
    {
        egg_log() << "Cannot read non existing file" << d->file;
        return false;
    }

    d->valid = d->tag.read();
    d->duration.setSecs(d->tag.duration());

    const QDateTime modified = info.lastModified();
    if (modified.isNull() || !modified.isValid())
    {
        egg_log() << "Cannot get last modification time" << d->file;
        return false;
    }
    d->modified = modified.toSecsSinceEpoch();

    return d->valid;
}

void swap(Audio &lhs, Audio &rhs)
{
    using std::swap;

    swap(lhs.d, rhs.d);
}
