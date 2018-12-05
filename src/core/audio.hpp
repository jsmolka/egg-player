#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <memory>

#include "core/cover.hpp"
#include "core/duration.hpp"
#include "core/tag.hpp"

struct AudioPrivate;

class Audio
{
public:
    Audio();
    Audio(const Audio &rhs);
    explicit Audio(const QString &file);

    Audio &operator=(Audio rhs);
    bool operator==(const Audio &rhs) const;

    void setFile(const QString &file);
    QString file() const;

    void setValid(bool valid);
    bool isValid() const;

    void setCached(bool cached);
    bool isCached() const;

    void setOutdated(bool outdated);
    bool isOutdated() const;

    void setModified(qint64 modified);
    qint64 modified() const;

    const Tag &tag() const;
    Tag &tag();

    const Cover &cover() const;
    Cover &cover();

    const Duration &duration() const;
    Duration &duration();

    bool read();

    friend void swap(Audio &lhs, Audio &rhs);

private:
    std::shared_ptr<AudioPrivate> d;
};

#endif // AUDIO_HPP
