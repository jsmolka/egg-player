#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <QFileInfo>
#include <QObject>
#include <QVector>

#include "cover.hpp"
#include "duration.hpp"
#include "types.hpp"

class Audio : public QObject
{
    Q_OBJECT

public:
    using vector = QVector<Audio *>;

    explicit Audio(QObject *parent = nullptr);
    Audio(const QString &file, QObject *parent = nullptr);
    Audio(const QString &file,
          const QString &title,
          const QString &artist,
          const QString &album,
          const QString &genre,
          int year,
          int track,
          int duration,
          int coverId,
          qint64 modified,
          QObject *parent = nullptr);

    void setValid(bool valid);
    bool isValid() const;

    void setCached(bool cached);
    bool isCached() const;

    void setOutdated(bool outdated);
    bool isOutdated() const;

    void setFile(const File &file);
    File file() const;

    void setTitle(const QString &title);
    QString title() const;

    void setArtist(const QString &artist);
    QString artist() const;

    void setAlbum(const QString &album);
    QString album() const;

    void setGenre(const QString &genre);
    QString genre() const;

    void setYear(int year);
    int year() const;

    void setTrack(int track);
    int track() const;

    Duration &duration();
    Cover &cover();

    qint64 modified() const;
    QFileInfo info() const;

    void update();

    const wchar_t * wideFile() const;

    bool operator<(const Audio &other) const;
    bool operator>(const Audio &other) const;
    bool operator<=(const Audio &other) const;
    bool operator>=(const Audio &other) const;

    bool operator==(const QString &other) const;
    bool operator==(const Audio &other) const;
    bool operator!=(const QString &other) const;
    bool operator!=(const Audio &other) const;

signals:
    void updated(Audio *audio);

private:
    bool readTags();

    bool m_valid;
    bool m_cached;
    bool m_outdated;

    QString m_file;
    QString m_title;
    QString m_artist;
    QString m_album;
    QString m_genre;

    int m_year;
    int m_track;

    Duration m_duration;
    Cover m_cover;

    qint64 m_modified;
};

#endif // AUDIO_HPP
