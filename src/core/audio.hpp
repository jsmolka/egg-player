#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <QVector>

#include "core/cover.hpp"
#include "core/duration.hpp"
#include "core/macros.hpp"
#include "core/tag.hpp"

class Audio
{
public:
    using vector = QVector<Audio *>;

    Audio();
    explicit Audio(const QString &file);

    static Audio *readFromFile(const QString &file);

    void setFile(const QString &file);
    QString file() const;

    EGG_PPROP(bool, valid, setValid, isValid)
    EGG_PPROP(bool, cached, setCached, isCached)
    EGG_PPROP(bool, outdated, setOutdated, isOutdated)
    EGG_PPROP(qint64, modified, setModified, modified)

    const Tag &tag() const;
    const Cover &cover() const;
    const Duration &duration() const;

    Tag &tag();
    Cover &cover();
    Duration &duration();

    bool read();

private:
    QString m_file;
    Tag m_tag;
    Cover m_cover;
    Duration m_duration;
};

#endif // AUDIO_HPP
