#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <QImage>
#include <QPixmap>
#include <QString>
#include <QUrl>

#include <taglib/attachedpictureframe.h>
#include <taglib/fileref.h>
#include <taglib/id3v2tag.h>
#include <taglib/id3v2frame.h>
#include <taglib/mpegfile.h>
#include <taglib/tag.h>

#include "src/constants/constant.hpp"

class Audio
{
public:
    Audio();
    Audio(QString path);

    bool operator==(const Audio &other);

    bool isValid() const;
    QString path() const;
    QString title() const;
    QString artist() const;
    QString album() const;
    QString genre() const;
    int year() const;
    int track() const;
    int length() const;
    QUrl url() const;

    int seconds() const;
    int minutes() const;
    QPixmap cover(int size);

private:
    bool readTags();
    QPixmap resizeCover(QPixmap image, int size);
    QPixmap readCover();

    bool m_isValid;
    QString m_path;
    QString m_title;
    QString m_artist;
    QString m_album;
    QString m_genre;
    int m_year;
    int m_track;
    int m_length;
    QUrl m_url;
};

#endif // AUDIO_HPP
