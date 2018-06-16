#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <QPainter>
#include <QPixmap>
#include <QPixmapCache>
#include <QVector>

#include <taglib/attachedpictureframe.h>
#include <taglib/fileref.h>
#include <taglib/id3v2tag.h>
#include <taglib/id3v2frame.h>
#include <taglib/mpegfile.h>
#include <taglib/tag.h>

#include "constants.hpp"
#include "logger.hpp"
#include "util.hpp"

class Audio
{
public:
    Audio(const QString &path);
    Audio(const QString &path, const QString &title, const QString &artist, const QString &album,
          const QString &genre, int year, int track, int duration, int coverId, int size);
    ~Audio();

    bool isValid() const;
    QString path() const;
    QString title() const;
    QString artist() const;
    QString album() const;
    QString genre() const;
    int year() const;
    int track() const;
    int duration(bool seconds = true) const;
    void setCoverId(int coverId);
    int coverId() const;
    quint64 size() const;
    bool isOutdated() const;

    const wchar_t * pathWChar() const;
    QPixmap cover(int size = 200);

private:
    bool readTags();
    QPixmap coverify(const QPixmap &cover);
    QPixmap readCover();

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
    quint64 m_size;
    bool m_outdated;
};

typedef QVector<Audio *> Audios;

#endif // AUDIO_HPP
