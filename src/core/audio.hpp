#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <QPixmap>
#include <QVector>

#include "logger.hpp"
#include "tag.hpp"

class Audio
{
public:
    Audio(const QString &path);
    Audio(const QString &path, const QString &title, const QString &artist, const QString &album,
          const QString &genre, int year, int track, int duration, int coverId);
    ~Audio();

    bool isValid() const;

    QString path() const;
    QString title() const;
    QString artist() const;
    QString album() const;
    QString genre() const;
    int year() const;
    int track() const;
    int duration() const;

    void setCoverId(int coverId);
    int coverId() const;

    void setCached(bool cached);
    bool isCached() const;

    const wchar_t * pathWChar() const;
    QPixmap cover(int size = 200);

private:
    bool readTags();

    bool m_valid;
    QString m_path;
    QString m_title;
    QString m_artist;
    QString m_album;
    QString m_genre;
    int m_year;
    int m_track;
    int m_duration;
    int m_coverId;
    bool m_cached;
};

typedef QVector<Audio *> Audios;

#endif // AUDIO_HPP
