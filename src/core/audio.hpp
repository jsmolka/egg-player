#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <QVector>

#include "cover.hpp"
#include "duration.hpp"
#include "logger.hpp"
#include "tag.hpp"

class Audio
{
public:
    Audio(const QString &path);
    Audio(const QString &path,
          const QString &title,
          const QString &artist,
          const QString &album,
          const QString &genre,
          int year,
          int track,
          int duration,
          int coverId);
    ~Audio();

    bool isValid() const;

    void setCached(bool cached);
    bool isCached() const;

    QString path() const;
    QString title() const;
    QString artist() const;
    QString album() const;
    QString genre() const;

    int year() const;
    int track() const;

    Duration * duration();
    Cover * cover();

    const wchar_t * widePath() const;

private:
    bool readTags();

    bool m_valid;
    bool m_cached;

    QString m_path;
    QString m_title;
    QString m_artist;
    QString m_album;
    QString m_genre;

    int m_year;
    int m_track;

    Duration m_duration;
    Cover m_cover;
};

typedef QVector<Audio *> Audios;

#endif // AUDIO_HPP
