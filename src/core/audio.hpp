#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <QtMath>
#include <QPainter>
#include <QPixmap>

#include <taglib/attachedpictureframe.h>
#include <taglib/fileref.h>
#include <taglib/id3v2tag.h>
#include <taglib/id3v2frame.h>
#include <taglib/mpegfile.h>
#include <taglib/tag.h>

#include "constants.hpp"
#include "logger.hpp"
#include "utils.hpp"

class Audio
{
public:
    Audio(const QString &path);
    ~Audio();

    bool isValid() const;
    QString path() const;
    QString title() const;
    QString artist() const;
    QString album() const;
    QString genre() const;
    int year() const;
    int track() const;
    int length(bool seconds = true) const;

    const wchar_t * pathWChar() const;
    QPixmap cover(int size = 200);

private:
    bool readTags();
    QPixmap readCover();

    bool m_valid;
    QString m_path;
    QString m_title;
    QString m_artist;
    QString m_album;
    QString m_genre;
    int m_year;
    int m_track;
    int m_length;
};

#endif // AUDIO_HPP
